#include <fstream>
#include <queue>

struct dijkstra_vertex {
    int number;
    int length;
    dijkstra_vertex* parent;
};

std::vector<std::pair<int, int>>* adjacency_list;
int num_start_vertex;
int num_finish_vertex;
auto cmp = [](dijkstra_vertex* first, dijkstra_vertex* second) {
    return first->length > second->length;
};
int* is_check_vertices;
int result_length;
std::vector<int> result_way;

void dijkstra(std::priority_queue<dijkstra_vertex*, std::vector<dijkstra_vertex*>, decltype(cmp)>& queue) {
    if (queue.empty()) {
        return;
    }

    auto cur_vertex = queue.top();

    queue.pop();

    if (is_check_vertices[cur_vertex->number] != 2) {
        is_check_vertices[cur_vertex->number]++;

        if (is_check_vertices[num_finish_vertex] == 2) {
            result_length = cur_vertex->length;

            dijkstra_vertex* cur_parent = cur_vertex;

            while (cur_parent != nullptr) {
                result_way.push_back(cur_parent->number);

                cur_parent = cur_parent->parent;
            }

            return;
        }

        for (auto& pair : adjacency_list[cur_vertex->number]) {
            if (is_check_vertices[pair.first] != 2) {
                auto* vertex = new dijkstra_vertex;

                vertex->number = pair.first;
                vertex->length = pair.second + cur_vertex->length;
                vertex->parent = cur_vertex;

                queue.push(vertex);
            }
        }
    }

    dijkstra(queue);
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

    std::priority_queue<dijkstra_vertex*, std::vector<dijkstra_vertex*>, decltype(cmp)> queue(cmp);
    is_check_vertices = new int[num_vertices]();
    auto* start_vertex = new dijkstra_vertex;

    start_vertex->number = num_start_vertex;
    start_vertex->length = 0;
    start_vertex->parent = nullptr;

    queue.push(start_vertex);

    dijkstra(queue);

    out << result_length << '\n';

    for (int i = result_way.size() - 1; i > 0; i--) {
        out << result_way[i] + 1 << ' ';
    }

    out << num_finish_vertex + 1;

    in.close();
    out.close();

    return 0;
}
