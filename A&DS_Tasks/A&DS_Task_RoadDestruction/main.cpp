#include <fstream>
#include <algorithm>
#include <stack>

int dsu_find(int* dsu, int num) {
    std::stack<int> stack;

    while (dsu[num] > 0) {
        stack.push(num);

        num = dsu[num];
    }

    while (!stack.empty()) {
        dsu[stack.top()] = num;

        stack.pop();
    }

    return num;
}

void dsu_union(int* dsu, int num1, int num2, int& num_connect_components) {
    int root1 = dsu_find(dsu, num1);
    int root2 = dsu_find(dsu, num2);
    int max_root;
    int min_root;

    if (root1 == root2) {
        return;
    }
    else if (dsu[root1] == dsu[root2]) {
        if (root1 >= root2) {
            max_root = root1;
            min_root = root2;
        }
        else {
            max_root = root2;
            min_root = root1;
        }
    }
    else if (std::abs(dsu[root1]) > std::abs(dsu[root2])) {
        max_root = root1;
        min_root = root2;
    }
    else {
        max_root = root2;
        min_root = root1;
    }

    dsu[max_root] += dsu[min_root];
    dsu[min_root] = max_root;
    num_connect_components--;
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_cities;
    int num_roads;
    int num_destructions;

    in >> num_cities >> num_roads >> num_destructions;

    auto* roads = new std::pair<int, int>[num_roads];

    for (int i = 0; i < num_roads; i++) {
        in >> roads[i].first >> roads[i].second;

        roads[i].first--;
        roads[i].second--;
    }

    bool* isBroke = new bool[num_roads]();
    int* destructions = new int[num_destructions];

    for (int i = 0; i < num_destructions; i++) {
        int num_road;
        in >> num_road;

        destructions[i] = --num_road;
        isBroke[num_road] = true;
    }

    int num_connect_components = num_cities;
    int* dsu = new int[num_cities];
    std::fill_n(dsu, num_cities, -1);

    for (int i = 0; i < num_roads; i++) {
        if (!isBroke[i]) {
            dsu_union(dsu, roads[i].first, roads[i].second, num_connect_components);
        }
    }

    int num_destruction = num_destructions - 1;

    while (num_connect_components > 1) {
        int num_road = destructions[num_destruction];

        dsu_union(dsu, roads[num_road].first, roads[num_road].second, num_connect_components);

        num_destruction--;
    }

    num_destruction++;

    for (int i = 0; i < num_destruction; i++) {
        out << 1;
    }

    for (int i = num_destruction; i < num_destructions; i++) {
        out << 0;
    }

    in.close();
    out.close();

    return 0;
}
