#include <iostream>
#include <fstream>
#include <vector>

void dfs(int** connect_matrix, int size, int num, bool* check_vertex, std::vector<int>* spanning_tree, int& numEdges) {
    check_vertex[num] = true;

    for (int i = 0; i < size; i++) {
        if (connect_matrix[num][i] == 1 && !check_vertex[i]) {
            spanning_tree[num].push_back(i + 1);
            numEdges++;

            dfs(connect_matrix, size, i, check_vertex, spanning_tree, numEdges);
        }
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int numVertex = 0;
    input >> numVertex;

    int** connect_matrix = new int*[numVertex];
    auto* spanning_tree = new std::vector<int>[numVertex];

    for (int i = 0; i < numVertex; i++) {
        connect_matrix[i] = new int[numVertex];
    }

    for (int i = 0; i < numVertex; i++) {
        for (int j = 0; j < numVertex; j++) {
            int num = 0;
            input >> num;

            connect_matrix[i][j] = num;
        }
    }

    bool* check_vertices = new bool[numVertex]();
    int numEdges = 0;

    dfs(connect_matrix, numVertex, 0, check_vertices, spanning_tree, numEdges);

    for (int i = 0; i < numVertex; i++) {
        if (!check_vertices[i]) {
            output << -1;

            return 0;
        }
    }

    output << numEdges << "\n";

    for (int i = 0; i < numVertex; i++) {
        for (int j = 0; j < spanning_tree[i].size(); j++) {
            output << i + 1 << " " << spanning_tree[i][j] << "\n";
        }
    }

    input.close();
    output.close();

    return 0;
}