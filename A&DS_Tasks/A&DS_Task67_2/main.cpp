#include <fstream>

int num_vertices;
bool** adjacency_matrix;
bool* is_check;
int* numbers;

void dfs(int& number, int num_vertex) {
    numbers[num_vertex] = number;
    is_check[num_vertex] = true;
    number++;

    for (int i = 0; i < num_vertices; i++) {
        if (adjacency_matrix[num_vertex][i] && !is_check[i]) {
            dfs(number, i);
        }
    }
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    in >> num_vertices;

    adjacency_matrix = new bool*[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        adjacency_matrix[i] = new bool[num_vertices]();

        for (int j = 0; j < num_vertices; j++) {
            in >> adjacency_matrix[i][j];
        }
    }

    numbers = new int[num_vertices]();
    is_check = new bool[num_vertices]();
    int number = 1;
    int cur_num_vertex = 0;

    while (cur_num_vertex < num_vertices) {
        dfs(number, cur_num_vertex);

        while (cur_num_vertex < num_vertices) {
            if (!is_check[cur_num_vertex]) {
                break;
            }

            cur_num_vertex++;
        }
    }

    for (int i = 0; i < num_vertices - 1; i++) {
        out << numbers[i] << ' ';
    }

    out << numbers[num_vertices - 1];

    in.close();
    out.close();

    return 0;
}
