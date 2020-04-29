#include <fstream>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_nodes;
    int num_edges;

    in >> num_nodes >> num_edges;

    bool** adjacency_matrix = new bool*[num_nodes];

    for (int i = 0; i < num_nodes; i++) {
        adjacency_matrix[i] = new bool[num_nodes]();
    }

    for (int i = 0; i < num_edges; i++) {
        int num_node1;
        int num_node2;

        in >> num_node1 >> num_node2;
        num_node1--;
        num_node2--;

        adjacency_matrix[num_node1][num_node2] = true;
        adjacency_matrix[num_node2][num_node1] = true;
    }

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes - 1; j++) {
            out << adjacency_matrix[i][j] << ' ';
        }

        out << adjacency_matrix[i][num_nodes - 1] << '\n';
    }

    in.close();
    out.close();

    return 0;
}
