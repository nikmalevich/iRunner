#include <fstream>
#include <vector>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_vertices;
    int num_edges;

    in >> num_vertices >> num_edges;

    auto* adjacency_list = new std::vector<int>[num_vertices];

    for (int i = 0; i < num_edges; i++) {
        int num_vertex1;
        int num_vertex2;

        in >> num_vertex1 >> num_vertex2;

        adjacency_list[num_vertex1 - 1].push_back(num_vertex2);
        adjacency_list[num_vertex2 - 1].push_back(num_vertex1);
    }

    for (int i = 0; i < num_vertices; i++) {
        int deg_vertex = adjacency_list[i].size();

        if (deg_vertex == 0) {
            out << deg_vertex << '\n';

            continue;
        }

        out << deg_vertex << ' ';

        for (int j = 0; j < deg_vertex - 1; j++) {
            out << adjacency_list[i][j] << ' ';
        }

        out << adjacency_list[i][deg_vertex - 1] << '\n';
    }

    in.close();
    out.close();

    return 0;
}
