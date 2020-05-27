#define _USE_MATH_DEFINES

#include <fstream>
#include <vector>
#include <cmath>

int num_postcards;
int* postcards_for_envelopes;
int* envelopes_for_postcards;
bool** adjacency_matrix;

bool is_fit(const std::pair<int, int>& postcard, const std::pair<int, int>& envelope) {
    double postcard_diag = sqrt(postcard.first * postcard.first + postcard.second * postcard.second);
    int max_envelope_side;
    int min_envelope_side;
    int max_postcard_side;
    int min_postcard_side;

    if (envelope.first >= envelope.second) {
        max_envelope_side = envelope.first;
        min_envelope_side = envelope.second;
    }
    else {
        max_envelope_side = envelope.second;
        min_envelope_side = envelope.first;
    }

    if (postcard.first >= postcard.second) {
        max_postcard_side = postcard.first;
        min_postcard_side = postcard.second;
    }
    else {
        max_postcard_side = postcard.second;
        min_postcard_side = postcard.first;
    }

    if ((max_postcard_side <= max_envelope_side) && (min_postcard_side <= min_envelope_side)) {
        return true;
    }

    if (max_postcard_side * min_postcard_side > max_envelope_side * min_envelope_side) {
        return false;
    }

    double bde = asin(1. * max_envelope_side / postcard_diag);
    double bdc = asin(1. * min_postcard_side / postcard_diag);
    double cde = bde - bdc;
    double daf = M_PI - cde;
    double caf = M_PI - daf - bdc;

    double result = cos(caf) * postcard_diag;

    return result <= min_envelope_side;
}

bool dfs(int num_vertex, bool* is_check) {
    for (int i = 0; i < num_postcards; i++) {
        if (adjacency_matrix[num_vertex][i] && !is_check[i]) {
            is_check[i] = true;

            if (envelopes_for_postcards[i] == -1) {
                postcards_for_envelopes[num_vertex] = i;
                envelopes_for_postcards[i] = num_vertex;

                return true;
            }
            else {
                if (dfs(envelopes_for_postcards[i], is_check)) {
                    postcards_for_envelopes[num_vertex] = i;
                    envelopes_for_postcards[i] = num_vertex;

                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    std::ifstream in("input.in");
    std::ofstream out("output.out");

    in >> num_postcards;

    auto* postcards = new std::pair<int, int>[num_postcards];
    auto* envelopes = new std::pair<int, int>[num_postcards];
    int height;
    int width;

    for (int i = 0; i < num_postcards; i++) {
        in >> height >> width;

        postcards[i] = std::pair<int, int>(height, width);
    }

    for (int i = 0; i < num_postcards; i++) {
        in >> height >> width;

        envelopes[i] = std::pair<int, int>(height, width);
    }

    adjacency_matrix = new bool*[num_postcards];

    for (int i = 0; i < num_postcards; i++) {
        adjacency_matrix[i] = new bool[num_postcards]();

        for (int j = 0; j < num_postcards; j++) {
            adjacency_matrix[i][j] = is_fit(postcards[i], envelopes[j]);
        }
    }

    bool is_found;
    int num_packed = 0;
    postcards_for_envelopes = new int[num_postcards];
    envelopes_for_postcards = new int[num_postcards];

    for (int i = 0; i < num_postcards; i++) {
        postcards_for_envelopes[i] = -1;
        envelopes_for_postcards[i] = -1;
    }

    do {
        is_found = false;

        for (int i = 0; i < num_postcards; i++) {
            auto* is_check = new bool[num_postcards]();

            if (postcards_for_envelopes[i] == -1) {
                if (dfs(i, is_check)) {
                    num_packed++;
                    is_found = true;
                }
            }
        }
    } while (is_found);

    if (num_packed == num_postcards) {
        out << "YES";
    }
    else {
        out << "NO\n" << num_packed;
    }

    in.close();
    out.close();

    return 0;
}
