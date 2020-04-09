#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>

struct Point {
    int x;
    int y;
    int num;
};

double get_length(const Point& point1, const Point& point2) {
    return std::sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
}

double get_max_diagonal(const Point& point1, const Point& point2, double** lengths, double** max_diagonals, int num_points, Point* points) {
    if (max_diagonals[point1.num][point2.num] == 0) {
        if ((point1.num == point2.num) || (((point1.num + 1) % num_points) == (point2.num % num_points))) {
            max_diagonals[point1.num][point2.num] = 0;
        }
        else if (((point1.num + 2) % num_points) == (point2.num % num_points)) {
            max_diagonals[point1.num][point2.num] = lengths[point1.num][point2.num];
        }
        else {
            int num_point = (point1.num + 1) % num_points;
            double min_diagonal = INT_MAX;

            while (num_point != point2.num) {
                max_diagonals[point1.num][num_point] = get_max_diagonal(point1, points[num_point], lengths, max_diagonals, num_points, points);
                max_diagonals[num_point][point2.num] = get_max_diagonal(points[num_point], point2, lengths, max_diagonals, num_points, points);

                double diagonal = std::max(lengths[point1.num][point2.num], std::max(max_diagonals[point1.num][num_point], max_diagonals[num_point][point2.num]));

                if (diagonal < min_diagonal) {
                    min_diagonal = diagonal;
                }

                num_point = (num_point + 1) % num_points;
            }

            max_diagonals[point1.num][point2.num] = min_diagonal;
        }
    }

    return max_diagonals[point1.num][point2.num];
}

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int num_points;
    in >> num_points;

    auto* points = new Point[num_points];

    for (int i = 0; i < num_points; i++) {
        in >> points[i].x;
        in >> points[i].y;

        points[i].num = i;
    }

    auto** lengths = new double*[num_points];

    for (int i = 0; i < num_points; i++) {
        lengths[i] = new double[num_points];

        for (int j = 0; j < num_points; j++) {
            lengths[i][j] = get_length(points[i], points[j]);
        }
    }

    auto** max_diagonals = new double*[num_points];

    for (int i = 0; i < num_points; i++) {
        max_diagonals[i] = new double[num_points]();
    }

    double min_diagonal = INT_MAX;

    for (int i = 0; i < num_points; i++) {
        int j = (i + num_points - 2) % num_points;

        max_diagonals[i][j] = get_max_diagonal(points[i], points[j], lengths, max_diagonals, num_points, points);

        if (max_diagonals[i][j] < min_diagonal) {
            min_diagonal = max_diagonals[i][j];
        }
    }

    out << std::fixed << std::setprecision(2) << min_diagonal;

    in.close();
    out.close();

    return 0;
}