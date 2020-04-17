#include <fstream>
#include <vector>
#include <queue>

void check_school(std::vector<int>* distributor_schools, bool* check_schools, std::queue<int>& queue, int& num_checks) {
    if (queue.empty()) {
        return;
    }

    int index = queue.front();

    queue.pop();

    for (int school : distributor_schools[index]) {
        if (!check_schools[school]) {
            check_schools[school] = true;
            num_checks--;

            queue.push(school);
        }
    }

    check_school(distributor_schools, check_schools, queue, num_checks);
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_schools;
    in >> num_schools;

    auto* distributor_schools = new std::vector<int>[num_schools];
    auto* recipient_schools = new std::vector<int>[num_schools];
    int index_max_size = 0;
    int max_size = 0;

    for (int i = 0; i < num_schools; i++) {
        int num_school;
        in >> num_school;

        distributor_schools[i].push_back(i);
        recipient_schools[i].push_back(i);

        while (num_school != 0) {
            num_school--;

            distributor_schools[i].push_back(num_school);
            recipient_schools[num_school].push_back(i);

            in >> num_school;
        }

        if (max_size < distributor_schools[i].size()) {
            max_size = distributor_schools[i].size();
            index_max_size = i;
        }
    }

    std::vector<int> max_distributor_schools;
    bool* check_schools = new bool[num_schools]();
    int num_checks = num_schools - 1;
    int num_distributor = 1;
    std::queue<int> queue;

    queue.push(index_max_size);
    check_schools[index_max_size] = true;
    max_distributor_schools.push_back(index_max_size);

    check_school(distributor_schools, check_schools, queue, num_checks);

    while (num_checks > 0) {
        num_distributor++;
        int *num_distributions = new int[num_schools]();

        for (int i = 0; i < num_schools; i++) {
            if (!check_schools[i]) {
                for (int school : recipient_schools[i]) {
                    num_distributions[school]++;
                }
            }
        }

        index_max_size = 0;
        max_size = 0;

        for (int i = 0; i < num_schools; i++) {
            if (max_size < num_distributions[i]) {
                max_size = num_distributions[i];
                index_max_size = i;
            }
        }

        queue.push(index_max_size);
        check_schools[index_max_size] = true;
        max_distributor_schools.push_back(index_max_size);
        num_checks--;

        check_school(distributor_schools, check_schools, queue, num_checks);
    }

    out << num_distributor << '\n';

    in.close();
    out.close();

    return 0;
}
