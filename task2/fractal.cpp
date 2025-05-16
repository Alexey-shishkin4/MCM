#include <iostream>
#include <complex>
#include <fstream>
#include <cmath>

using namespace std;
using cd = complex<double>;

const int MAX_ITER = 30;
const double EPS = 1e-6;
const double ROOT_EPS = 1e-3;

// Метод Ньютона для z^3 = 1
cd newton(cd z0) {
    for (int i = 0; i < MAX_ITER; ++i) {
        cd f = pow(z0, 3) - cd(1, 0);
        cd df = 3.0 * pow(z0, 2);
        if (abs(df) < 1e-10) break;
        cd z1 = z0 - f / df;
        if (abs(z1 - z0) < EPS)
            return z1;
        z0 = z1;
    }
    return z0;
}

// Сравнивает корень с ранее найденными (корни формируются по мере нахождения)
int find_or_add_root(cd z, cd roots[], int& root_count) {
    for (int i = 0; i < root_count; ++i) {
        if (abs(z - roots[i]) < ROOT_EPS)
            return i;
    }
    if (root_count < 3) {
        roots[root_count++] = z;
        return root_count - 1;
    }
    return -1;
}

int main() {
    int width = 600, height = 600;
    double xmin = -2.0, xmax = 2.0;
    double ymin = -2.0, ymax = 2.0;

    cd roots[3]; // Будем находить корни сами
    int root_count = 0;

    ofstream fout("fractal_data.csv");
    fout << "x,y,root\n";

    for (int i = 0; i < height; ++i) {
        double y = ymin + (ymax - ymin) * i / height;
        for (int j = 0; j < width; ++j) {
            double x = xmin + (xmax - xmin) * j / width;
            cd z0 = cd(x, y);
            cd res = newton(z0);
            int root_id = find_or_add_root(res, roots, root_count);
            fout << x << "," << y << "," << root_id << "\n";
        }
    }

    fout.close();

    cout << "Найдено корней: " << root_count << "\n";
    for (int i = 0; i < root_count; ++i)
        cout << "root[" << i << "] = " << roots[i] << "\n";

    cout << "Файл fractal_data.csv записан.\n";
    return 0;
}
