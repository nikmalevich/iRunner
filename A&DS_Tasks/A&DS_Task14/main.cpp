#include <fstream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> routes;

void dfs(std::vector<std::pair<int, int>>* graph, std::queue<std::pair<int, int>>& queue, bool* is_check_node, int num_node, int num_destination_node) {
    if (queue.empty()) {
        return;
    }

    if (num_node == num_destination_node) {
        std::vector<int> rout;
        int length = 0;

        while (!queue.empty()) {
            rout.push_back(queue.front().first);
            length += queue.front().second;

            queue.pop();
        }

        rout.push_back(length);
        routes.push_back(rout);

        return;
    }

    is_check_node[num_node] = true;

    for (std::pair<int, int>& pair : graph[num_node]) {
        if (!is_check_node[pair.first]) {
            std::queue<std::pair<int, int>> new_queue = std::queue(queue);

            new_queue.push(pair);

            dfs(graph, new_queue, is_check_node, pair.first, num_destination_node);
        }
    }
}

int main() {
    std::ifstream in("input.in");
    std::ofstream out("output.out");

    int num_cities;
    int num_roads;

    in >> num_cities >> num_roads;

    auto* graph = new std::vector<std::pair<int, int>>[num_cities];

    for (int i = 0; i < num_roads; i++) {
        int num_city1;
        int num_city2;
        int length;

        in >> num_city1 >> num_city2 >> length;

        graph[num_city1 - 1].emplace_back(num_city2 - 1, length);
    }

    int num_city1;
    int num_city2;

    in >> num_city1 >> num_city2;

    num_city1--;
    num_city2--;

    std::queue<std::pair<int, int>> queue;
    bool* is_check_node = new bool[num_cities]();

    queue.push(std::pair<int, int>(num_city1, 0));

    dfs(graph, queue, is_check_node, num_city1, num_city2);

    for (std::vector<int>& rout : routes) {
        for (int city : rout) {
            out << city << ' ';
        }

        out << '\n';
    }

    in.close();
    out.close();

    return 0;
}
