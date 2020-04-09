#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int numVertex = 0;
    input >> numVertex;

    int numEdges = 0;
    input >> numEdges;

    auto* vertexes = new std::vector<int>[numVertex];

    for (int i = 0; i < numVertex; i++) {
        vertexes[i].push_back(0);
    }

    for (int i = 0; i < numEdges; i++) {
        int vertex1 = 0;
        int vertex2 = 0;

        input >> vertex1;
        input >> vertex2;

        vertexes[vertex1 - 1].push_back(vertex2);
        vertexes[vertex2 - 1].push_back(vertex1);

        vertexes[vertex1 - 1][0]++;
        vertexes[vertex2 - 1][0]++;
    }

    for (int i = 0; i < numVertex; i++) {
        for (int j = 0; j < vertexes[i].size() - 1; j++) {
            output << vertexes[i][j] << " ";
        }

        output << vertexes[i][vertexes[i].size() - 1] << "\n";
    }

    input.close();
    output.close();

    return 0;
}