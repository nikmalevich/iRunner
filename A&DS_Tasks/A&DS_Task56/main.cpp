#include <fstream>
#include <vector>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    long long n;
    in >> n;
    std::vector<int> powers;

    int cur_power = 0;
    long long cur_num = 1;

    while ((cur_num << 1) <= n) {
        cur_num = cur_num << 1;
        cur_power++;
    }

    powers.push_back(cur_power);

    n -= cur_num;

    while (n > 0) {
        while (cur_num > n) {
            cur_num = cur_num >> 1;
            cur_power--;
        }

        powers.push_back(cur_power);

        n -= cur_num;
    }

    for (int i = powers.size() - 1; i >= 0; i--) {
        out << powers[i] << '\n';
    }

    in.close();
    out.close();

    return 0;
}
