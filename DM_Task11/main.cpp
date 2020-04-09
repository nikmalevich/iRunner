#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int num_vertices = 0;
    int num_edges = 0;

    input >> num_vertices;
    input >> num_edges;

    auto* adjacency_list = new std::vector<int>[num_vertices];

    bool is_multigraph = false;

    for (int i = 0; i < num_edges; i++) {
        int num_vertex1 = 0;
        int num_vertex2 = 0;

        input >> num_vertex1;
        input >> num_vertex2;

        num_vertex1--;
        num_vertex2--;

        if (num_vertex1 == num_vertex2) {
            output << "No\n";
            output << "No\n";
            output << "Yes";

            input.close();
            output.close();

            return 0;
        }

        if (!is_multigraph) {
            if (std::find(adjacency_list[num_vertex1].begin(), adjacency_list[num_vertex1].end(), num_vertex2) != adjacency_list[num_vertex1].end()) {
                is_multigraph = true;
            }
        }

        adjacency_list[num_vertex1].push_back(num_vertex2);
        adjacency_list[num_vertex2].push_back(num_vertex1);
    }

    if (is_multigraph) {
        output << "No\n";
        output << "Yes\n";
        output << "Yes";
    }
    else {
        output << "Yes\n";
        output << "Yes\n";
        output << "Yes";
    }

    input.close();
    output.close();

    return 0;
}