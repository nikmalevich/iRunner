#include <fstream>
#include <vector>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_matrix;
    in >> num_matrix;

    std::vector<std::pair<int, int>> matrices;
    int** dynamic_matrix = new int*[num_matrix];

    for (int i = 0; i < num_matrix; i++) {
        std::pair<int, int> matrix;
        in >> matrix.first;
        in >> matrix.second;

        matrices.push_back(matrix);

        dynamic_matrix[i] = new int[num_matrix];
    }

    for (int j = 0; j < num_matrix; j++) {
        dynamic_matrix[j][j] = 0;

        for (int i = j - 1; i >= 0; i--) {
            int min = INT_MAX;

            for (int k = i; k < j; k++) {
                min = std::min(min, dynamic_matrix[i][k] + dynamic_matrix[k + 1][j] + matrices[i].first * matrices[k].second * matrices[j].second);
            }

            dynamic_matrix[i][j] = min;
        }
    }

    out << dynamic_matrix[0][num_matrix - 1];

    in.close();
    out.close();

    return 0;
}
