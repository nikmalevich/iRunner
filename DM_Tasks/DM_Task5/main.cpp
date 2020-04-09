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

    for (int i = 0; i < numVertex; i++) {
        for (int j = 0; j < numVertex; j++) {
            int num = 0;

            input >> num;

            if (num == 1) {
                vertexes[j] = i + 1;
            }
        }
    }

    for (int i = 0; i < numVertex - 1; i++) {
        output << vertexes[i] << " ";
    }

    output << vertexes[numVertex - 1];

    input.close();
    output.close();

    return 0;
}