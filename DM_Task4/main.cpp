#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int numVertex = 0;
    input >> numVertex;

    int* vertexes = new int[numVertex];

    for (int i = 0; i < numVertex; i++) {
        vertexes[i] = 0;
    }

    for (int i = 0; i < numVertex - 1; i++) {
        int vertex1 = 0;
        int vertex2 = 0;

        input >> vertex1;
        input >> vertex2;

        vertexes[vertex2 - 1] = vertex1;
    }

    for (int i = 0; i < numVertex - 1; i++) {
            output << vertexes[i] << " ";
    }

    output << vertexes[numVertex - 1];

    input.close();
    output.close();

    return 0;
}