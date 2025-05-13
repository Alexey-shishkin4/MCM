#include <iostream>
#include <complex>
#include <fstream>
#include <cmath>

using namespace std;
using cd = complex<double>;


#define M_PI 3.14159265358979323846


cd roots[3] = {
    cd(1, 0),
    polar(1.0, 2 * M_PI / 3),
    polar(1.0, 4 * M_PI / 3)
};

int find_root(cd z) {
    for (int i = 0; i < 3; ++i)
        if (abs(z - roots[i]) < 1e-4)
            return i;
    return -1;
}

cd newton(cd z0) {
    for (int i = 0; i < 30; ++i) {
        cd f = pow(z0, 3) - cd(1, 0);
        cd df = 3.0 * pow(z0, 2);
        if (abs(df) < 1e-10) break;
        z0 -= f / df;
    }
    return z0;
}

int main() {
    int width = 600, height = 600;
    double xmin = -2.0, xmax = 2.0;
    double ymin = -2.0, ymax = 2.0;

    ofstream fout("fractal_data.csv");
    fout << "x,y,root\n";

    for (int i = 0; i < height; ++i) {
        double y = ymin + (ymax - ymin) * i / height;
        for (int j = 0; j < width; ++j) {
            double x = xmin + (xmax - xmin) * j / width;
            cd z = cd(x, y);
            cd result = newton(z);
            int root_id = find_root(result);
            fout << x << "," << y << "," << root_id << "\n";
        }
    }
    cout << "Корни уравнения z^3 = 1:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "root[" << i << "] = " << roots[i] << "\n";
    }

    fout.close();
    std::cout << "Файл fractal_data.csv записан.\n";
    return 0;
}
