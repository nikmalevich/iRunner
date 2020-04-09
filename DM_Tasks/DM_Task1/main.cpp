#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int numVertex = 0;
    input >> numVertex;

    int numEdges = 0;
    input >> numEdges;

    int* vertexes = new int[numVertex];

    for (int i = 0; i < numVertex; i++) {
        vertexes[i] = 0;
    }

    for (int i = 0; i < numEdges; i++) {
        int vertex1 = 0;
        int vertex2 = 0;

        input >> vertex1;
        input >> vertex2;

        vertexes[vertex1 - 1]++;
        vertexes[vertex2 - 1]++;
    }

    std::qsort(vertexes, numVertex, sizeof(*vertexes), [](const void* a, const void* b)
    {
        int arg1 = *static_cast<const int*>(a);
        int arg2 = *static_cast<const int*>(b);

        return arg2 - arg1;
    });

    for (int i = 0; i < numVertex - 1; i++) {
        output << vertexes[i] << " ";
    }

    output << vertexes[numVertex - 1];

    input.close();
    output.close();

    return 0;
}