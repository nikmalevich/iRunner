#include <iostream>
#include <fstream>

void colorize(int** connect_matrix, int* coloring, bool* is_painted, int num_vertices, int num_vertex) {
    is_painted[num_vertex] = true;

    for (int i = 0; i < num_vertices; i++) {
        if (!is_painted[num_vertices]) {
            return;
        }

        if (connect_matrix[num_vertex][i] == 1) {
            if (is_painted[i] && coloring[num_vertex] == coloring[i]) {
                is_painted[num_vertices] = false;

                return;
            }

            if (!is_painted[i]) {
                coloring[i] = 3 - coloring[num_vertex];

                colorize(connect_matrix, coloring, is_painted, num_vertices, i);
            }
        }
    }
}

int main() {
    std::ifstream input("input.in");
    std::ofstream output("output.out");

    int num_vertices = 0;
    input >> num_vertices;

    int** connect_matrix = new int*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        connect_matrix[i] = new int[num_vertices];
    }

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            input >> connect_matrix[i][j];
        }
    }

    int* coloring = new int[num_vertices]();
    bool* is_painted = new bool[num_vertices + 1]();

    is_painted[num_vertices] = true;

    for (int i = 0; i < num_vertices; i++) {
        if (!is_painted[i]) {
            coloring[i] = i % 2 + 1;

            colorize(connect_matrix, coloring, is_painted, num_vertices, i);
        }
    }

    if (!is_painted[num_vertices]) {
        output << "NO";
    }
    else {
        output << "YES\n1";

        for (int i = 1; i < num_vertices; i++) {
            if (coloring[i] == 1) {
                output << " " << i + 1;
            }
        }
    }

    input.close();
    output.close();

    return 0;
}