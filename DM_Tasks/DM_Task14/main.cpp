#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <vector>

void bfs(std::vector<int>* connect, std::queue<int>& queue_vertices, bool* check_vertices, int* time, int num_vertex) {
    for (int vertex : connect[num_vertex]) {
        if(!check_vertices[vertex]) {
            queue_vertices.push(vertex);

            time[vertex] = time[num_vertex] + 1;
            check_vertices[vertex] = true;
        }
    }

    queue_vertices.pop();
}

int main() {
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    int num_vertices = 0;
    in >> num_vertices;

    auto* connect = new std::vector<int>[num_vertices];

    for (int i = 0; i < num_vertices; i++) {
        int deg = 0;
        in >> deg;

        for (; deg > 0; deg--) {
            int num_vertex = 0;
            in >> num_vertex;

            connect[i].push_back(num_vertex - 1);
        }
    }

    int result_num_vertex = 0;
    int result_time = 0;
    std::queue<int> queue_vertices;

    for (int i = 0; i < num_vertices; i++) {
        int* time = new int[num_vertices]();
        bool* check_vertices = new bool[num_vertices]();
        int number_check = 0;

        queue_vertices.push(i);
        time[i] = 0;
        check_vertices[i] = true;

        while (!queue_vertices.empty()) {
            bfs(connect, queue_vertices, check_vertices, time, queue_vertices.front());
            number_check++;
        }

        if (number_check == num_vertices) {
            int max_time = *std::max_element(time, time + num_vertices);

            if (result_time <= max_time) {
                result_time = max_time;
                result_num_vertex = i + 1;
            }
        }
    }

    if (result_time == 0) {
        if (num_vertices != 1) {
            out << "impossible";
        }
        else {
            out << "0\n1";
        }
    }
    else {
        out << result_time << "\n" << result_num_vertex;
    }

    in.close();
    out.close();

    return 0;
}