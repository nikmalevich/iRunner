#include <fstream>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int length;
    in >> length;

    int* arr = new int[length];

    in >> arr[0];

    for (int i = 1; i < length; i++) {
        in >> arr[i];

        if (arr[i] < arr[(i - 1) / 2]) {
            out << "No";

            in.close();
            out.close();

            return 0;
        }
    }

    out << "Yes";

    in.close();
    out.close();

    return 0;
}
