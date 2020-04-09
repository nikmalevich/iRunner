#include <iostream>
#include <fstream>
#include <vector>

void dfs(int** connect_matrix, bool* check_vertices, int num_vertices, int num_vertex) {
    check_vertices[num_vertex] = true;

    for (int i = 0; i < num_vertices; i++) {
        if (connect_matrix[num_vertex][i] == 1 && !check_vertices[i]) {
            dfs(connect_matrix, check_vertices, num_vertices, i);
        }
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int num_edges = 0;
    input >> num_edges;

    int num_vertices = 7;

    int** connect_matrix = new int*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        connect_matrix[i] = new int[num_vertices]();
    }

    int* deg_vertices = new int[num_vertices]();

    for (int i = 0; i < num_edges; i++) {
        int num_vertex1 = 0;
        int num_vertex2 = 0;

        input >> num_vertex1;
        input >> num_vertex2;

        deg_vertices[num_vertex1]++;
        deg_vertices[num_vertex2]++;

        connect_matrix[num_vertex1][num_vertex2] = 1;
        connect_matrix[num_vertex2][num_vertex1] = 1;
    }

    bool* check_vertices = new bool[num_vertices]();

    int index = 0;
    while (deg_vertices[index] == 0) {
        index++;
    }

    dfs(connect_matrix, check_vertices, num_vertices, index);

    for (int i = 0; i < num_vertices; i++) {
        if (deg_vertices[i] != 0 && (deg_vertices[i] % 2 == 1 || !check_vertices[i])) {
            output << "No";

            return 0;
        }
    }

    output << "Yes";

    input.close();
    output.close();

    return 0;
}