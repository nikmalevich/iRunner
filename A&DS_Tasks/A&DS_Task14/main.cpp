#include <fstream>
#include <queue>
#include <algorithm>

std::vector<std::pair<int, int>>* adjacency_list;
int num_start_vertex;
int num_finish_vertex;
auto cmp = [](std::pair<int, int> first, std::pair<int, int> second) {
    return first.second > second.second;
};
int* is_check_vertex;
int* dijkstra_arr;
int length;

void dijkstra(std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)>& queue) {
    auto cur_pair = queue.top();

    queue.pop();
    is_check_vertex[cur_pair.first]++;

    if(is_check_vertex[num_finish_vertex] == 2) {
        length = cur_pair.second;

        return;
    }

    for (auto& pair : adjacency_list[cur_pair.first]) {
        if (is_check_vertex[pair.first] != 2) {
            queue.push(std::pair<int, int>(pair.first, pair.second + cur_pair.second));
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

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> queue(cmp);
    is_check_vertex = new int[num_vertices]();
    dijkstra_arr = new int[num_vertices]();

    queue.push(std::pair<int, int>(num_start_vertex, 0));
    length = 0;
    std::fill(dijkstra_arr, dijkstra_arr + num_vertices, INT_MAX);
    dijkstra_arr[num_start_vertex] = 0;

    dijkstra(queue);

    in.close();
    out.close();

    return 0;
}
