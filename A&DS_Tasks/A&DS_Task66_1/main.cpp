#include <fstream>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_vertices;

    in >> num_vertices;

    int* canonical_arr = new int[num_vertices]();

    for (int i = 0; i < num_vertices - 1; i++) {
        int num_vertex1;
        int num_vertex2;

        in >> num_vertex1 >> num_vertex2;

        canonical_arr[num_vertex2 - 1] = num_vertex1;
    }

    for (int i = 0; i < num_vertices - 1; i++) {
        out << canonical_arr[i] << ' ';
    }

    out << canonical_arr[num_vertices - 1];

    in.close();
    out.close();

    return 0;
}
