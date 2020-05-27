#include <iostream>
#include <vector>
#include <queue>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int num_vertices;
    int num_edges;

    std::cin >> num_vertices >> num_edges;

    auto* adjacency_list = new std::vector<std::pair<int, int>>[num_vertices];

    for (int i = 0; i < num_edges; i++) {
        int num_vertex1;
        int num_vertex2;
        int weight;

        std::cin >> num_vertex1 >> num_vertex2 >> weight;
        num_vertex1--;
        num_vertex2--;

        adjacency_list[num_vertex1].emplace_back(num_vertex2, weight);
        adjacency_list[num_vertex2].emplace_back(num_vertex1, weight);
    }

    long long result_length;
    auto* is_check_vertices = new bool[num_vertices]();
    auto cmp = [](std::pair<int, long long> first, std::pair<int, long long> second) {
        return first.second > second.second;
    };
    std::priority_queue<std::pair<int, long long>, std::vector<std::pair<int, long long>>, decltype(cmp)> queue(cmp);

    queue.push(std::pair<int, long long>(0, 0));

    while (true) {
        auto cur_vertex = queue.top();

        queue.pop();

        if (is_check_vertices[cur_vertex.first]) {
            continue;
        }

        is_check_vertices[cur_vertex.first] = true;

        if (cur_vertex.first == num_vertices - 1) {
            result_length = cur_vertex.second;

            break;
        }

        for (auto& vertex : adjacency_list[cur_vertex.first]) {
            if (!is_check_vertices[vertex.first]) {
                queue.push(std::pair<int, long long>(vertex.first, cur_vertex.second + vertex.second));
            }
        }
    }

    std::cout << result_length;

    return 0;
}