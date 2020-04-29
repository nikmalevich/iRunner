#include <fstream>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_vertices;

    in >> num_vertices;

    int* canonical_arr = new int[num_vertices]();

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            bool is_arc;

            in >> is_arc;

            if (is_arc) {
                canonical_arr[j] = i + 1;
            }
        }
    }

    for (int i = 0; i < num_vertices - 1; i++) {
        out << canonical_arr[i] << ' ';
    }

    out << canonical_arr[num_vertices - 1];

    in.close();
    out.close();

    return 0;
}
