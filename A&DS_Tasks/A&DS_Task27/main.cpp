#include <fstream>
#include <vector>
#include <queue>

void bfs(std::vector<int>* graph, bool* recipients, std::queue<int>& queue) {
    if (queue.empty()) {
        return;
    }

    int index = queue.front();

    queue.pop();

    for (int num_school : graph[index]) {
        if (!recipients[num_school]) {
            recipients[num_school] = true;

            queue.push(num_school);
        }
    }

    bfs(graph, recipients, queue);
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_schools;
    in >> num_schools;

    auto* graph = new std::vector<int>[num_schools];
    auto** distributor_matrix = new bool*[num_schools];

    for (int i = 0; i < num_schools; i++) {
        distributor_matrix[i] = new bool[num_schools]();

        int num_school;
        in >> num_school;

        while (num_school != 0) {
            num_school--;

            graph[i].push_back(num_school);

            in >> num_school;
        }
    }

    int max_distributor = 0;
    int index_max_distributor = 0;

    for (int i = 0; i < num_schools; i++) {
        int num_recipients = 0;
        std::queue<int> queue;
        auto* recipients = new bool[num_schools]();

        queue.push(i);
        recipients[i] = true;

        bfs(graph, recipients, queue);

        for (int j = 0; j < num_schools; j++) {
            if (recipients[j]) {
                num_recipients++;
                distributor_matrix[i][j] = true;
            }
        }

        if (max_distributor < num_recipients) {
            max_distributor = num_recipients;
            index_max_distributor = i;
        }
    }

    int num_recipients = num_schools - max_distributor;
    auto* recipients = new bool[num_schools]();
    int num_distributors = 1;

    for (int i = 0; i < num_schools; i++) {
        recipients[i] = distributor_matrix[index_max_distributor][i];
    }

    while (num_recipients > 0) {
        num_distributors++;
        int* num_useful_recipients = new int[num_schools]();

        for (int i = 0; i < num_schools; i++) {
            if (!recipients[i]) {
                for (int j = 0; j < num_schools; j++) {
                    if (distributor_matrix[j][i]) {
                        num_useful_recipients[j]++;
                    }
                }
            }
        }

        max_distributor = 0;
        index_max_distributor = 0;

        for (int i = 0; i < num_schools; i++) {
            if (max_distributor < num_useful_recipients[i]) {
                max_distributor = num_useful_recipients[i];
                index_max_distributor = i;
            }
        }

        for (int i = 0; i < num_schools; i++) {
            if ((!recipients[i]) && distributor_matrix[index_max_distributor][i]) {
                recipients[i] = true;
            }
        }

        num_recipients -= max_distributor;
    }

    out << num_distributors << '\n';

    bool* schools = new bool[num_schools]();
    std::vector<std::vector<int>> connection_components;

    for (int i = 0; i < num_schools; i++) {
        if (!schools[i]) {
            std::vector<int> connection_component;

            for (int j = 0; j < num_schools; j++) {
                if (distributor_matrix[i][j] && distributor_matrix[j][i]) {
                    schools[j] = true;
                    connection_component.push_back(j);
                }
            }

            connection_components.push_back(connection_component);
        }
    }

    int num_components = connection_components.size();

    if (num_components == 1) {
        out << 0;

        in.close();
        out.close();

        return 0;
    }

    bool* is_distributor_components = new bool[num_components]();
    bool* is_recipients_components = new bool[num_components]();

    for (int i = 0; i < num_components; i++) {
        for (int j = i + 1; j < num_components; j++) {
            for (int num_school1 : connection_components[i]) {
                for (int num_school2 : connection_components[j]) {
                    if (distributor_matrix[num_school1][num_school2]) {
                        is_distributor_components[i] = true;
                        is_recipients_components[j] = true;
                    }

                    if (distributor_matrix[num_school2][num_school1]) {
                        is_distributor_components[j] = true;
                        is_recipients_components[i] = true;
                    }
                }
            }
        }
    }

    int num_not_distributor_components = 0;
    int num_not_recipients_components = 0;

    for (int i = 0; i < num_components; i++) {
        if (!is_distributor_components[i]) {
            num_not_distributor_components++;
        }
        if (!is_recipients_components[i]) {
            num_not_recipients_components++;
        }
    }

    out << std::max(num_not_distributor_components, num_not_recipients_components);

    return 0;
}
