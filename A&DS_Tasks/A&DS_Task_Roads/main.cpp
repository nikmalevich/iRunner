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

    in >> num_cities;
    in >> num_roads;

    int num_connect_components = num_cities;
    int* dsu = new int[num_cities];
    std::fill_n(dsu, num_cities, -1);

    for (int i = 0; i < num_roads; i++) {
        int city1;
        int city2;

        in >> city1;
        in >> city2;

        city1--;
        city2--;

        dsu_union(dsu, city1, city2, num_connect_components);

        out << num_connect_components << '\n';
    }

    in.close();
    out.close();

    return 0;
}
