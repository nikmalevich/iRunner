#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

void bfs(char** map, int num_line, int num_column, int* time, int width, int length) {
    time[num_line * width + num_column] = 0;
    bool* check_vertices = new bool[width * length]();
    std::queue<std::vector<int>> queue_vertices;
    std::vector<int> temp_ver;
    temp_ver.push_back(num_line);
    temp_ver.push_back(num_column);
    temp_ver.push_back(0);
    queue_vertices.push(temp_ver);
    int i, j, weight, num_ver;

    while (!queue_vertices.empty()) {
        temp_ver = queue_vertices.front();
        queue_vertices.pop();
        i = temp_ver[0];
        j = temp_ver[1];
        weight = temp_ver[2];
        check_vertices[i * width + j] = true;

        if (i != 0 && !check_vertices[(i - 1) * width + j] && map[i - 1][j] != '#') {
            temp_ver[0] = i - 1;
            temp_ver[1] = j;
            temp_ver[2] = weight + 1;
            queue_vertices.push(temp_ver);
            num_ver = temp_ver[0] * width + temp_ver[1];

            if (temp_ver[2] < time[num_ver]) {
                time[num_ver] = temp_ver[2];
            }
        }
        if (i != (length - 1) && !check_vertices[(i + 1) * width + j] && map[i + 1][j] != '#') {
            temp_ver[0] = i + 1;
            temp_ver[1] = j;
            temp_ver[2] = weight + 1;
            queue_vertices.push(temp_ver);
            num_ver = temp_ver[0] * width + temp_ver[1];

            if (temp_ver[2] < time[num_ver]) {
                time[num_ver] = temp_ver[2];
            }
        }
        if (j != 0 && !check_vertices[i * width + j - 1] && map[i][j - 1] != '#') {
            temp_ver[0] = i;
            temp_ver[1] = j - 1;
            temp_ver[2] = weight + 1;
            queue_vertices.push(temp_ver);
            num_ver = temp_ver[0] * width + temp_ver[1];

            if (temp_ver[2] < time[num_ver]) {
                time[num_ver] = temp_ver[2];
            }
        }
        if (j != (width - 1) && !check_vertices[i * width + j + 1] && map[i][j + 1] != '#') {
            temp_ver[0] = i;
            temp_ver[1] = j + 1;
            temp_ver[2] = weight + 1;
            queue_vertices.push(temp_ver);
            num_ver = temp_ver[0] * width + temp_ver[1];

            if (temp_ver[2] < time[num_ver]) {
                time[num_ver] = temp_ver[2];
            }
        }
    }
}

int main() {
    std::ifstream in("vampires.in");
    std::ofstream out("vampires.out");

    int length;
    int width;

    in >> length;
    in >> width;

    char** map = new char*[length];
    for (int i = 0; i < length; i++) {
        map[i] = new char[width];
    }

    char str[2000];
    in.getline(str, 2000);

    for (int i = 0; i < length; i++) {
        in.getline(str, 2000);

        for (int j = 0; j < width; j++) {
            map[i][j] = str[j];
        }
    }

    int num_vertices = length * width;

    int* time = new int[num_vertices];
    std::fill_n(time, num_vertices, INT_MAX);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == 'V') {
                bfs(map, i, j, time, width, length);
            }
        }
    }

    int max_time = 0;
    qsort(time, num_vertices, sizeof(int), [](const void* a, const void* b)
    {
        int arg1 = *static_cast<const int*>(a);
        int arg2 = *static_cast<const int*>(b);

        if(arg1 < arg2) return -1;
        if(arg1 > arg2) return 1;
        return 0;
    });

    for (int i = num_vertices - 1; i >= 0; i--) {
        if (time[i] < INT_MAX) {
            max_time = time[i];

            break;
        }
    }

    out << max_time;

    in.close();
    out.close();

    return 0;
}