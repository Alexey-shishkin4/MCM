#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <vector>


#define M_PI 3.14159265358979323846

//============================================================
// 1) Уравнение tan(x) = x
//    f(x) = tan(x) - x
//============================================================

// Функция f(x)
double f(double x) {
    return std::tan(x) - x;
}

// Производная f'(x) для метода Ньютона
// f'(x) = sec^2(x) - 1
double df(double x) {
    // sec^2(x) = 1 + tan^2(x)
    // => sec^2(x) - 1 = tan^2(x)
    // Либо напрямую: sec^2(x) - 1 = tan^2(x)
    // Оставим форму sec^2(x) - 1, для наглядности:
    return 1.0 / std::cos(x) / std::cos(x) - 1.0;
}

//------------------------------------------------------------
// 1a) Метод бисекции (деления пополам) для f(x) = 0
//------------------------------------------------------------
double bisectionMethod(double a, double b, double tol, int maxIter) {
    // Предполагается, что f(a) и f(b) имеют разные знаки!
    double fa = f(a);
    double fb = f(b);
    if (fa * fb > 0.0) {
        std::cerr << "Ошибка: f(a) и f(b) должны иметь разные знаки!\n";
        return NAN;
    }

    double mid;
    for (int i = 0; i < maxIter; i++) {
        mid = 0.5 * (a + b);
        double fmid = f(mid);

        if (std::fabs(fmid) < tol) {
            break;
        }
        // Смотрим знак
        if (fa * fmid <= 0.0) {
            b = mid;
            fb = fmid;
        } else {
            a = mid;
            fa = fmid;
        }
    }
    return mid;
}

//------------------------------------------------------------
// 1b) Метод простых итераций (fixed point iteration)
//    tan(x) = x -> x = arctan(x)
//    Схема: x_{n+1} = arctan(x_n)
//------------------------------------------------------------
double fixedPointIteration(double x0, double tol, int maxIter) {
    double x = x0;
    for (int i = 0; i < maxIter; i++) {
        double xNext = std::atan(x);
        if (std::fabs(xNext - x) < tol) {
            return xNext;
        }
        x = xNext;
    }
    return x;
}

//------------------------------------------------------------
// 1c) Метод Ньютона для уравнения f(x) = 0
//------------------------------------------------------------
double newtonMethod(double x0, double tol, int maxIter) {
    double x = x0;
    for (int i = 0; i < maxIter; i++) {
        double fVal = f(x);
        double dfVal = df(x);
        // Проверка, чтобы не делить на 0
        if (std::fabs(dfVal) < 1e-14) {
            std::cerr << "Производная близка к нулю. Прекращение итераций.\n";
            return x;
        }

        double xNext = x - fVal / dfVal;
        if (std::fabs(xNext - x) < tol) {
            return xNext;
        }
        x = xNext;
    }
    return x;
}

//------------------------------------------------------------
// 1d) Метод секущих для уравнения f(x) = 0
//    Для секущих нужны две стартовые точки x0 и x1
//------------------------------------------------------------
double secantMethod(double x0, double x1, double tol, int maxIter) {
    double f0 = f(x0);
    double f1 = f(x1);

    for (int i = 0; i < maxIter; i++) {
        if (std::fabs(f1 - f0) < 1e-14) {
            std::cerr << "Знаменатель близок к нулю. Прекращение итераций.\n";
            return x1;
        }
        double x2 = x1 - f1 * (x1 - x0) / (f1 - f0);

        if (std::fabs(x2 - x1) < tol) {
            return x2;
        }
        // Сдвигаем точки
        x0 = x1;
        x1 = x2;
        f0 = f1;
        f1 = f(x2);
    }
    return x1;
}

//============================================================
// 2) Решение полинома z^3 - 1 = 0 методом Ньютона в C++
//    И определение областей притяжения к корням.
//============================================================

// f(z) = z^3 - 1
// f'(z) = 3z^2
std::complex<double> F(const std::complex<double>& z) {
    return std::pow(z, 3) - std::complex<double>(1.0, 0.0);
}

std::complex<double> dF(const std::complex<double>& z) {
    return 3.0 * std::pow(z, 2);
}

// Итерация Ньютона в комплексной плоскости
// z_{n+1} = z_n - f(z_n) / f'(z_n)
std::complex<double> newtonComplex(std::complex<double> z0, double tol, int maxIter) {
    std::complex<double> z = z0;
    for (int i = 0; i < maxIter; i++) {
        std::complex<double> fz = F(z);
        std::complex<double> dfz = dF(z);

        // Проверка, чтобы не делить на 0
        if (std::abs(dfz) < 1e-14) {
            // Считаем, что производная слишком мала
            return z;
        }

        std::complex<double> zNext = z - fz / dfz;
        if (std::abs(zNext - z) < tol) {
            return zNext;
        }
        z = zNext;
    }
    return z;
}

// Функция, которая возвращает номер корня (0,1,2), к которому "притянуло" z0
// Корни уравнения z^3=1: 1, e^{i 2π/3}, e^{i 4π/3}
int whichRoot(const std::complex<double>& z) {
    // Явные корни:
    static std::vector<std::complex<double>> roots = {
        std::complex<double>(1.0, 0.0),
        std::polar(1.0, 2.0*M_PI/3.0),
        std::polar(1.0, 4.0*M_PI/3.0)
    };

    // Ищем, к какому корню ближе всего
    double minDist = std::abs(z - roots[0]);
    int minIndex = 0;
    for (int i = 1; i < (int)roots.size(); i++) {
        double dist = std::abs(z - roots[i]);
        if (dist < minDist) {
            minDist = dist;
            minIndex = i;
        }
    }
    return minIndex;
}

int main() {
    std::cout << std::fixed << std::setprecision(8);

    //========================================================
    // 1) Уравнение tan(x) = x
    //========================================================
    std::cout << "=== Уравнение tan(x) = x ===\n";

    // Для уравнения tan(x) = x существует бесконечно много корней,
    // но самый очевидный — x=0. Также есть корни около ±4.4934, ±7.7253, и так далее.
    // Для наглядности найдем корень рядом с 0.

    double a = -1.0, b = 1.0;
    double tol = 1e-8;
    int maxIter = 100;

    // Проверим f(a)*f(b)<0 для бисекции:
    std::cout << "Метод бисекции:\n";
    double rootBisect = bisectionMethod(a, b, tol, maxIter);
    std::cout << "  Корень ~ " << rootBisect << "\n";
    std::cout << "  Проверка f(root) ~ " << f(rootBisect) << "\n\n";

    // Метод простых итераций
    std::cout << "Метод простых итераций:\n";
    double x0 = 0.5; // Старт с 0.5
    double rootFixed = fixedPointIteration(x0, tol, maxIter);
    std::cout << "  Корень ~ " << rootFixed << "\n";
    std::cout << "  Проверка f(root) ~ " << f(rootFixed) << "\n\n";

    // Метод Ньютона
    std::cout << "Метод Ньютона:\n";
    x0 = 0.5; // Старт с 0.5
    double rootNewton = newtonMethod(x0, tol, maxIter);
    std::cout << "  Корень ~ " << rootNewton << "\n";
    std::cout << "  Проверка f(root) ~ " << f(rootNewton) << "\n\n";

    // Метод секущих
    std::cout << "Метод секущих:\n";
    double x1 = -0.5; // Две разные стартовые точки
    double rootSecant = secantMethod(x0, x1, tol, maxIter);
    std::cout << "  Корень ~ " << rootSecant << "\n";
    std::cout << "  Проверка f(root) ~ " << f(rootSecant) << "\n\n";

    //========================================================
    // 2) Полином z^3 - 1 = 0
    //    Определение корней и их областей притяжения
    //========================================================
    std::cout << "=== Полином z^3 - 1 = 0 ===\n";
    std::cout << "Явные корни: 1, e^{i 2π/3}, e^{i 4π/3}.\n";
    std::cout << "Метод Ньютона для комплексных z.\n\n";

    // Можно проверить сходу итерации из различных начальных точек
    // и посмотреть, к какому корню они придут.
    // Для демонстрации - переберём несколько точек вручную:

    std::vector<std::complex<double>> initialPoints = {
        { 2.0, 0.0 }, // Стартовая точка 2 + 0i
        {-1.0, 1.0 }, // -1 + i
        { 0.5, -0.5},
        {-2.0, -1.0},
        { 1.0, 0.5 },
    };

    for (auto& z0 : initialPoints) {
        std::complex<double> zRes = newtonComplex(z0, 1e-12, 100);
        int idx = whichRoot(zRes);
        std::cout << "Старт z0 = (" << z0.real() << "," << z0.imag()
                  << ") => итог z = (" << zRes.real() << "," << zRes.imag()
                  << "), близко к корню #" << idx << "\n";
    }

    // Чтобы действительно построить «области притяжения»,
    // обычно делают сетку в комплексной плоскости (например, от -2 до 2 по Re(z),
    // от -2 до 2 по Im(z)), в каждой точке итерируют метод Ньютона и смотрят,
    // к какому корню сходится. После чего раскрашивают разные области в разные цвета.
    // Здесь же мы ограничились текстовой иллюстрацией.

    return 0;
}
