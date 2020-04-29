#include <fstream>
#include <algorithm>
#include <vector>

int* list;
int** arc_list;
int num_start_node;
int num_finish_node;
int length_min_way;
int length_second_min_way;
std::vector<std::vector<int>> ways;
std::vector<std::vector<int>> cycles;

void dfs(std::vector<int>& way, int num_node) {
    if (num_node == num_finish_node) {
        if (way[0] < length_min_way) {
            length_second_min_way = length_min_way;
            length_min_way = way[0];
        } else if (way[0] > length_min_way && way[0] < length_second_min_way) {
            length_second_min_way = way[0];
        }

        ways.push_back(way);
    }

    int num_next_arc = list[num_node];
    int num_next_node = arc_list[num_next_arc][0];

    while (num_next_node != 0) {
        if (std::find(way.begin(), way.end(), num_next_arc) == way.end()) {
            std::vector<int> new_way(way);

            new_way.push_back(num_next_arc);
            new_way[0] += arc_list[num_next_arc][1];

            dfs(new_way, num_next_node);
        } else {
            cycles.push_back(way);
        }

        num_next_arc = arc_list[num_next_arc][2];
        num_next_node = arc_list[num_next_arc][0];
    }
}

int main() {
    std::ifstream in("input.in");
    std::ofstream out("output.out");

    int num_nodes;
    int num_arcs;

    in >> num_nodes >> num_arcs;

    list = new int[num_nodes + 1]();
    arc_list = new int*[num_arcs + 1];

    arc_list[0] = new int[3]();

    for (int i = 1; i <= num_arcs; i++) {
        int num_node1;
        int num_node2;
        int weight;

        in >> num_node1 >> num_node2 >> weight;
        arc_list[i] = new int[3]();

        arc_list[i][0] = num_node2;
        arc_list[i][1] = weight;
        arc_list[i][2] = list[num_node1];

        list[num_node1] = i;
    }

    in >> num_start_node >> num_finish_node;

    std::vector<int> start_way;
    length_min_way = INT_MAX;

    start_way.push_back(0);

    dfs(start_way, num_start_node);

    for (std::vector<int>& way : ways) {
        for (int num_arc : way) {
            out << num_arc << ' ';
        }

        out << '\n';
    }

    out << length_min_way << ' ' << length_second_min_way << '\n';

    for (std::vector<int>& cycle : cycles) {
        for (int num_arc : cycle) {
            out << num_arc << ' ';
        }

        out << '\n';
    }

//    for (int i = 1; i < num_nodes + 1; i++) {
//        out << list[i] << ' ';
//    }
//
//    out << '\n';
//
//    for (int i = 1; i < num_arcs + 1; i++) {
//        for (int j = 0; j < 3; j++) {
//            out << arc_list[i][j] << ' ';
//        }
//
//        out << '\n';
//    }



    in.close();
    out.close();

    return 0;
}
