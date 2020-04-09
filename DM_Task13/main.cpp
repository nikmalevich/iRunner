#include <iostream>
#include <fstream>

void dfs(bool** connect_matrix, int* vertex_order, int num_vertices, int num_vertex, int& index) {
    vertex_order[num_vertex] = index;
    index++;

    for (int i = 0; i < num_vertices; i++) {
        if (connect_matrix[num_vertex][i] && vertex_order[i] == 0) {
            dfs(connect_matrix, vertex_order, num_vertices, i, index);
        }
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int num_vertices = 0;
    input >> num_vertices;

    bool **connect_matrix = new bool *[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        connect_matrix[i] = new bool[num_vertices];
    }

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            input >> connect_matrix[i][j];
        }
    }

    int* vertex_order = new int[num_vertices]();
    int index = 1;

    for (int i = 0; i < num_vertices; i++) {
        if (vertex_order[i] == 0) {
            dfs(connect_matrix, vertex_order, num_vertices, i, index);
        }
    }

    output << vertex_order[0];

    for (int i = 1; i < num_vertices; i++) {
        output << " " << vertex_order[i];
    }

    input.close();
    output.close();

    return 0;
}