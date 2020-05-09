#include <fstream>
#include <vector>
#include <cmath>

int num_postcards;
int* postcards_for_envelopes;
bool* is_packed_postcards;
int num_left_pack;
int num_packed;
bool** adjacency_matrix;
int* envelopes_for_postcards;

bool is_fit(const std::pair<int, int>& postcard, const std::pair<int, int>& envelope) {
    int postcard_diag2 = postcard.first * postcard.first + postcard.second * postcard.second;
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

    double new_postcard_x1 = sqrt(1. * (postcard_diag2 - max_envelope_side * max_envelope_side) / 4);

    if (new_postcard_x1 == 0) {
        return max_envelope_side == min_postcard_side;
    }

    if (new_postcard_x1 != new_postcard_x1) {
        return (max_postcard_side <= max_envelope_side && min_postcard_side <= min_envelope_side);
    }

    double tg_a = 1. * max_envelope_side / 2 / new_postcard_x1;
    double cos_a2 = 1 / (1 + tg_a * tg_a);
    double sin_a2 = 1 - cos_a2;
    double new_postcard_x2 = sqrt(cos_a2) * max_postcard_side / 2 + sqrt(sin_a2) * min_postcard_side / 2;

    return (max_postcard_side <= max_envelope_side && min_postcard_side <= min_envelope_side) || (2 * new_postcard_x2 <= min_envelope_side);
}

void light_packing(int start_index) {
    bool is_pack;

    do {
        is_pack = false;

        for (int i = start_index; i < num_postcards; i++) {
            if ((postcards_for_envelopes[i] == 0) && !is_packed_postcards[i]) {
                is_packed_postcards[i] = true;
                num_left_pack--;
            }

            if (postcards_for_envelopes[i] == 1) {
                is_pack = true;
                is_packed_postcards[i] = true;
                num_left_pack--;
                num_packed++;

                int num_envelope = 0;

                while (adjacency_matrix[i][num_envelope] == 0) {
                    num_envelope++;
                }

                envelopes_for_postcards[num_envelope] = INT_MAX;

                for (int j = start_index; j < num_postcards; j++) {
                    if (adjacency_matrix[j][num_envelope]) {
                        adjacency_matrix[j][num_envelope] = false;
                        postcards_for_envelopes[j]--;
                    }
                }
            }
        }
    } while (is_pack);
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
    postcards_for_envelopes = new int[num_postcards]();
    envelopes_for_postcards = new int[num_postcards]();

    for (int i = 0; i < num_postcards; i++) {
        adjacency_matrix[i] = new bool[num_postcards]();

        for (int j = 0; j < num_postcards; j++) {
            if (is_fit(postcards[i], envelopes[j])) {
                adjacency_matrix[i][j] = true;
                postcards_for_envelopes[i]++;
                envelopes_for_postcards[j]++;
            }
        }
    }

    is_packed_postcards = new bool[num_postcards]();
    num_packed = 0;
    num_left_pack = num_postcards;

    light_packing(0);

    for (int i = 0; i < num_postcards; i++) {
        if (!is_packed_postcards[i]) {
            is_packed_postcards[i] = true;
            num_left_pack--;

            int min_envelope = INT_MAX;
            int index_min_envelope = 0;

             for (int j = 0; j < num_postcards; j++) {
                 if (adjacency_matrix[i][j] && envelopes_for_postcards[j] < min_envelope) {
                     min_envelope = envelopes_for_postcards[j];
                     index_min_envelope = j;
                 }
             }

             if (min_envelope != INT_MAX) {
                 envelopes_for_postcards[index_min_envelope] = INT_MAX;
                 num_packed++;

                 for (int j = 0; j < num_postcards; j++) {
                     if (adjacency_matrix[j][index_min_envelope]) {
                         adjacency_matrix[j][index_min_envelope] = false;
                         postcards_for_envelopes[j]--;
                     }
                 }
             }

             light_packing(i + 1);
        }
    }

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
