#include <iostream>
#include <fstream>
#include <queue>

void bfs(bool** connect_matrix, std::queue<int>& queue_vertices, int* vertex_order, bool* check_vertices, int num_vertices, int num_vertex, int index) {
    for (int i = 0; i < num_vertices; i++) {
        if(connect_matrix[num_vertex][i] && !check_vertices[i]) {
            queue_vertices.push(i);

            check_vertices[i] = true;
        }
    }

    queue_vertices.pop();
    vertex_order[num_vertex] = index;
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int num_vertices = 0;
    input >> num_vertices;

    bool** connect_matrix = new bool*[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        connect_matrix[i] = new bool[num_vertices];
    }

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            input >> connect_matrix[i][j];
        }
    }

    std::queue<int> queue_vertices;
    int* vertex_order = new int[num_vertices]();
    bool* check_vertices = new bool[num_vertices]();
    int index = 1;

    for (int i = 0; i < num_vertices; i++) {
        if (vertex_order[i] == 0) {
            queue_vertices.push(i);
            check_vertices[i] = true;

            while (!queue_vertices.empty()) {
                bfs(connect_matrix, queue_vertices, vertex_order, check_vertices, num_vertices, queue_vertices.front(), index);

                index++;
            }
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