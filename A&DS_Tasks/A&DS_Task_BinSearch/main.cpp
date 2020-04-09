#include <iostream>

int first_occurrence(const int* array, int array_length, int num) {
    int first = 0;
    int last = array_length - 1;
    int mid = 0;

    while (first <= last) {
        mid = (first + last) / 2;

        if ((num == array[mid]) && ((mid == 0) || (num > array[mid - 1]))) {
            break;
        }

        if (num <= array[mid]) {
            last = mid - 1;
        }
        else {
            first = mid + 1;
        }
    }

    return mid;
}

int last_occurrence(const int* array, int array_length, int num) {
    int first = 0;
    int last = array_length - 1;
    int mid = 0;

    while (first <= last) {
        mid = (first + last) / 2;

        if ((num == array[mid]) && ((mid == array_length - 1) || num < array[mid + 1])) {
            break;
        }

        if (num >= array[mid]) {
            first = mid + 1;
        }
        else {
            last = mid - 1;
        }
    }

    return mid;
}

int main() {
    int array_length;
    std::cin >> array_length;

    int* array = new int[array_length];

    for (int i = 0; i < array_length; i++) {
        std::cin >> array[i];
    }

    int num_requests;
    std::cin >> num_requests;

    for (int i = 0; i < num_requests; i++) {
        int request;
        std::cin >> request;

        int first = first_occurrence(array, array_length, request);

        if (request == array[first]) {
            int last = last_occurrence(array, array_length, request);

            std::cout << 1 << " " << first << " " << last + 1 << "\n";
        }
        else if (request > array[first]) {
            std::cout << 0 << " " << first + 1 << " " << first + 1 << "\n";
        }
        else {
            std::cout << 0 << " " << first << " " << first << "\n";
        }
    }

    return 0;
}
