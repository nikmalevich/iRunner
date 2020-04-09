#include <iostream>
#include <fstream>

void dfs(int** connect_matrix, bool* check_vertices, int num_vertices, int num_vertex) {
    check_vertices[num_vertex] = true;

    for (int i = 0; i < num_vertices; i++) {
        if (connect_matrix[num_vertex][i] == 1 && !check_vertices[i]) {
            dfs(connect_matrix, check_vertices, num_vertices, i);
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

    bool* check_vertices = new bool[num_vertices]();

    dfs(connect_matrix, check_vertices, num_vertices, 0);

    for (int i = 0; i < num_vertices; i++) {
        if (!check_vertices[i]) {
            output << "NO";

            return 0;
        }
    }

    output << "YES";

    input.close();
    output.close();

    return 0;
}