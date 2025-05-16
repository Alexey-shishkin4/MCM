#include <iostream>
#include <cmath>

#define M_PI 3.14159265358979323846

const double EPS    = 1e-10;
const int    MAX_IT = 1000;

// f(x) = tan(x) - x
double f(double x) {
    return std::tan(x) - x;
}

// f'(x) = 1/cos^2(x) - 1
double df(double x) {
    double c = std::cos(x);
    return (std::fabs(c) < EPS ? 1e300 : (1.0/(c*c) - 1.0));
}


double bisection(double a, double b) {
    double fa = f(a), fb = f(b);
    if (fa*fb > 0) {
        std::cerr << "Ошибка бисекции: нет смены знака.\n";
        return NAN;
    }
    while (b - a > EPS) {
        double c = 0.5*(a + b), fc = f(c);
        if (fa*fc <= 0) { b = c; fb = fc; }
        else            { a = c; fa = fc; }
    }
    return 0.5*(a + b);
}

double newton(double x0) {
    for (int i = 0; i < MAX_IT; ++i) {
        double deriv = df(x0);
        if (std::fabs(deriv) < EPS) break;
        double x1 = x0 - f(x0)/deriv;
        if (std::fabs(x1 - x0) < EPS) return x1;
        x0 = x1;
    }
    return x0;
}

// Метод секущих
double secant(double x0, double x1) {
    double f0 = f(x0), f1 = f(x1);
    for (int i = 0; i < MAX_IT; ++i) {
        double denom = (f1 - f0);
        if (std::fabs(denom) < EPS) break;
        double x2 = x1 - f1*(x1 - x0)/denom;
        if (std::fabs(x2 - x1) < EPS) return x2;
        x0 = x1; f0 = f1;
        x1 = x2; f1 = f(x1);
    }
    return x1;
}

// Итерационный метод x = arctan(x) + k*pi
double fixed_point(double x0, int k) {
    for (int i = 0; i < MAX_IT; ++i) {
        double x1 = std::atan(x0) + k*M_PI;
        if (std::fabs(x1 - x0) < EPS) return x1;
        x0 = x1;
    }
    return x0;
}

// Интервал по номеру k
void interval_by_k(int k, double& a, double& b) {
    const double d = 1e-2;
    a = k*M_PI - M_PI/2 + d;
    b = k*M_PI + M_PI/2 - d;
}

int main() {
    int k;
    std::cout << "Введите номер интервала k: ";
    std::cin >> k;

    double a, b;
    interval_by_k(k, a, b);

    double mid      = 0.5*(a + b);
    double root_bis = bisection(a, b);
    double d = 1e-4;
    double root_new = newton(root_bis + d);
    double root_sec = secant(root_bis - d, root_bis + d);
    double root_it  = fixed_point(mid, k);

    std::cout.precision(15);
    std::cout << "\nИнтервал: ["<< a <<", "<< b <<"]\n";
    std::cout << "Бисекция:      " << root_bis << "\n";
    std::cout << "Ньютона:       " << root_new << "\n";
    std::cout << "Секущих:       " << root_sec << "\n";
    std::cout << "Итерационный:  " << root_it  << "\n";
    return 0;
}
