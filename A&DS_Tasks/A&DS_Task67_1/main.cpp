#include <fstream>
#include <queue>

std::vector<int>* adjacency_list;
std::queue<int> queue;
int* order_vertex;
int cur_order;

void bfs() {
    if (queue.empty()) {
        return;
    }

    int cur_num_vertex = queue.front();

    queue.pop();

    for (int num_vertex : adjacency_list[cur_num_vertex]) {
        if (order_vertex[num_vertex] == 0) {
            order_vertex[num_vertex] = cur_order;

            queue.push(num_vertex);
            cur_order++;
        }
    }

    bfs();
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_vertices;
    in >> num_vertices;

    adjacency_list = new std::vector<int>[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            bool is_arc;
            in >> is_arc;

            if (is_arc) {
                adjacency_list[i].push_back(j);
            }
        }
    }

    order_vertex = new int[num_vertices]();
    cur_order = 1;

    int min_num_not_check_vertex = num_vertices;

    for (int i = 0; i < num_vertices; i++) {
        if (order_vertex[i] == 0) {
            min_num_not_check_vertex = i;

            break;
        }
    }

    while (min_num_not_check_vertex != num_vertices) {
        order_vertex[min_num_not_check_vertex] = cur_order;

        queue.push(min_num_not_check_vertex);
        cur_order++;

        bfs();

        min_num_not_check_vertex = num_vertices;

        for (int i = 0; i < num_vertices; i++) {
            if (order_vertex[i] == 0) {
                min_num_not_check_vertex = i;

                break;
            }
        }
    }

    for (int i = 0; i < num_vertices - 1; i++) {
        out << order_vertex[i] << ' ';
    }

    out << order_vertex[num_vertices - 1];

    in.close();
    out.close();

    return 0;
}
