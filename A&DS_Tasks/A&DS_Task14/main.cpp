#pragma comment(linker, "/STACK:16777216")

#include <fstream>
#include <queue>

std::vector<std::pair<int, int>>* adjacency_list;
int num_start_vertex;
int num_finish_vertex;
auto cmp = [](std::pair<int, int> first, std::pair<int, int> second) {
    return first.second > second.second;
};
int* is_check_vertices;
int result_length;
std::vector<int> result_way;

void dijkstra(std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)>& queue) {
    if (queue.empty()) {
        return;
    }

    auto cur_pair = queue.top();

    queue.pop();

    if (is_check_vertices[cur_pair.first] != 2) {
        is_check_vertices[cur_pair.first]++;

        if (is_check_vertices[num_finish_vertex] == 2) {
            result_length = cur_pair.second;

            return;
        }

        for (auto& pair : adjacency_list[cur_pair.first]) {
            if (is_check_vertices[pair.first] != 2) {
                queue.push(std::pair<int, int>(pair.first, cur_pair.second + pair.second));
            }
        }
    }

    dijkstra(queue);
}

void dfs(std::vector<int>& way, int num_vertex) {
    if ((num_vertex == num_finish_vertex) && (way[0] == result_length)) {
        result_way = std::vector<int>(way);

        return;
    }

    is_check_vertices[num_vertex]++;

    for (auto& pair : adjacency_list[num_vertex]) {
        int way_size = way.size();
        int way_length = way[0];

        if ((is_check_vertices[pair.first] != 2) && (way[0] + pair.second <= result_length)) {
            way.push_back(pair.first);
            way[0] += pair.second;

            dfs(way, pair.first);

            if (!result_way.empty()) {
                return;
            }
        }

        way[0] = way_length;

        while (way.size() > way_size) {
            way.pop_back();
        }
    }
}

int main() {
    std::ifstream in("input.in");
    std::ofstream out("output.out");

    int num_vertices;
    int num_arcs;

    in >> num_vertices >> num_arcs;

    adjacency_list = new std::vector<std::pair<int, int>>[num_vertices];

    for (int i = 0; i < num_arcs; i++) {
        int num_vertex1;
        int num_vertex2;
        int weight;

        in >> num_vertex1 >> num_vertex2 >> weight;
        num_vertex1--;
        num_vertex2--;

        adjacency_list[num_vertex1].emplace_back(num_vertex2, weight);
    }

    in >> num_start_vertex >> num_finish_vertex;
    num_start_vertex--;
    num_finish_vertex--;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> queue(cmp);
    is_check_vertices = new int[num_vertices]();

    queue.push(std::pair<int, int>(num_start_vertex, 0));

    dijkstra(queue);

    std::vector<int> way;

    way.push_back(0);
    way.push_back(num_start_vertex);
    std::fill(is_check_vertices, is_check_vertices + num_vertices, 0);

    dfs(way, num_start_vertex);

    out << result_length << '\n';

    for (int i = 1; i < result_way.size() - 1; i++) {
        out << result_way[i] + 1 << ' ';
    }

    out << result_way[result_way.size() - 1] + 1;

    in.close();
    out.close();

    return 0;
}
