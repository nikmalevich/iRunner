#include <iostream>
#include <fstream>

void dfs(int** connect_matrix, int size, int num, bool* vertices) {
    vertices[num] = true;

    for (int i = 0; i < size; i++) {
        if (connect_matrix[num][i] == 1 && !vertices[i]) {
            dfs(connect_matrix, size, i, vertices);
        }
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int numVertex = 0;
    input >> numVertex;

    int numEdge = 0;

    int** connect_matrix = new int*[numVertex];

    for (int i = 0; i < numVertex; i++) {
        connect_matrix[i] = new int[numVertex];
    }

    for (int i = 0; i < numVertex; i++) {
        for (int j = 0; j < numVertex; j++) {
            int num = 0;
            input >> num;

            connect_matrix[i][j] = num;

            if (num == 1 && j > i) {
                numEdge++;
            }
        }
    }

    bool* vertices = new bool[numVertex]();

    dfs(connect_matrix, numVertex, 0, vertices);

    bool is_connected = true;

    for (int i = 0; i < numVertex; i++) {
        if (!vertices[i]) {
            is_connected = false;
            break;
        }
    }

    if (numVertex - numEdge == 1 && is_connected) {
        output << "Yes";
    }
    else {
        output << "No";
    }

    input.close();
    output.close();

    return 0;
}