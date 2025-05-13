#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>


#define M_PI 3.14159265358979323846

const double EPS = 1e-10;

double f(double x) {
    return tan(x) - x;
}

double df(double x) {
    return 1.0 / (cos(x) * cos(x)) - 1.0;
}

double bisection(double a, double b) {
    while ((b - a) > EPS) {
        double c = (a + b) / 2;
        if (f(a) * f(c) < 0) b = c;
        else a = c;
    }
    return (a + b) / 2;
}

//cos(4.5) ≈ -0.21
//1/cos² ≈ 22
//условие сжимающего отображения нарушено :(
//double iteration(double x0) {
//    for (int i = 0; i < 1000; ++i) {
//        double x1 = tan(x0);  // Новое значение x
//        if (fabs(x1 - x0) < EPS)  // Условие сходимости
//            return x1;
//        x0 = x1;
//    }
//    return x0;
//}

double iteration(double x0, int k) {
    for (int i = 0; i < 1000; ++i) {
        double x1 = atan(x0) + k * M_PI;  // Применение итерационной формулы
        if (fabs(x1 - x0) < EPS)  // Условие сходимости
            return x1;
        x0 = x1;
    }
    return x0;
}


double newton(double x0) {
    for (int i = 0; i < 1000; ++i) {
        double x1 = x0 - f(x0) / df(x0);
        if (fabs(x1 - x0) < EPS)
            return x1;
        x0 = x1;
    }
    return x0;
}

double secant(double x0, double x1) {
    for (int i = 0; i < 1000; ++i) {
        double fx0 = f(x0);
        double fx1 = f(x1);
        if (fabs(fx1 - fx0) < EPS) break;
        double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        if (fabs(x2 - x1) < EPS)
            return x2;
        x0 = x1;
        x1 = x2;
    }
    return x1;
}

int main() {
    std::cout.precision(15);
    std::cout << "Корень уравнения tan(x) = x:\n";
    std::cout << "Метод деления пополам: " << bisection(4.1, 4.9) << '\n';
    std::cout << "Метод Ньютона:         " << newton(4.5) << '\n';
    std::cout << "Метод секущих:         " << secant(4.4, 4.6) << '\n';
    std::cout << "Метод итераций:        " << iteration(1.0, 1) << '\n';

    return 0;
}
