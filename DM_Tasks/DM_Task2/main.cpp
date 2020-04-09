#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int numVertex = 0;
    input >> numVertex;

    int numEdges = 0;
    input >> numEdges;

    int** matrix = new int*[numVertex];

    for (int i = 0; i < numVertex; i++) {
        matrix[i] = new int[numVertex];
    }

    for (int i = 0; i < numEdges; i++) {
        int vertex1 = 0;
        int vertex2 = 0;

        input >> vertex1;
        input >> vertex2;

        matrix[vertex1 - 1][vertex2 - 1] = 1;
        matrix[vertex2 - 1][vertex1 - 1] = 1;
    }

    for (int i = 0; i < numVertex; i++) {
        for (int j = 0; j < numVertex - 1; j++) {
            if (matrix[i][j] != 1) {
                output << "0 ";
            }
            else {
                output << "1 ";
            }
        }

        if (matrix[i][numVertex - 1] != 1) {
            output << "0\n";
        }
        else {
            output << "1\n";
        }
    }

    input.close();
    output.close();

    return 0;
}