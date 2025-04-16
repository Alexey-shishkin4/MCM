#include <iostream>
#include <limits>
#include <cmath>

template<typename T>
void analyzePrecision(const std::string& name) {
    T epsilon = 1.0;
    int mantissaBits = 0;

    // Найти машинное ε
    while ((T)(1.0 + epsilon / 2.0) > 1.0) {
        epsilon /= 2.0;
        mantissaBits++;
    }

    std::cout << "Тип: " << name << std::endl;
    std::cout << "Машинное epsilon: " << epsilon << std::endl;
    std::cout << "Разрядов в мантиссе: " << mantissaBits << std::endl;

    // Минимальная и максимальная степени
    std::cout << "Минимальная степень: " << std::numeric_limits<T>::min_exponent << std::endl;
    std::cout << "Максимальная степень: " << std::numeric_limits<T>::max_exponent << std::endl;

    // Сравнение чисел
    T one = 1.0;
    T half_eps = epsilon / 2.0;
    T plus_half = one + half_eps;
    T plus_eps = one + epsilon;
    T plus_eps_and_half = one + epsilon + half_eps;

    std::cout << "\nСравнение чисел:\n";
    std::cout << "1 = " << one << std::endl;
    std::cout << "1 + ε/2 = " << plus_half << std::endl;
    std::cout << "1 + ε = " << plus_eps << std::endl;
    std::cout << "1 + ε + ε/2 = " << plus_eps_and_half << std::endl;
    std::cout << "--------------------------\n\n";
}

int main() {
    analyzePrecision<float>("float");
    analyzePrecision<double>("double");
    return 0;
}
