#include <fstream>
#include <queue>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_pushes;
    int num_gets;

    in >> num_pushes >> num_gets;

    int* numbers = new int[num_pushes];

    for (int i = 0; i < num_pushes; i++) {
        in >> numbers[i];
    }

    std::priority_queue<int> less_queue;
    std::priority_queue<int, std::vector<int>, std::greater<>> greater_queue;
    int need_num_get;
    int cur_num = 1;

    less_queue.push(numbers[0]);

    for (int i = 0; i < num_gets; i++) {
        in >> need_num_get;

        while (cur_num < need_num_get) {
            if (numbers[cur_num] > less_queue.top()) {
                greater_queue.push(numbers[cur_num]);
            }
            else {
                greater_queue.push(less_queue.top());
                less_queue.pop();
                less_queue.push(numbers[cur_num]);
            }

            cur_num++;
        }

        if (i == num_gets - 1) {
            out << less_queue.top();
        }
        else {
            out << less_queue.top() << ' ';
        }

        if (greater_queue.empty()) {
            less_queue.push(numbers[cur_num]);

            cur_num++;
        }
        else {
            less_queue.push(greater_queue.top());
            greater_queue.pop();
        }
    }

    in.close();
    out.close();

    return 0;
}
