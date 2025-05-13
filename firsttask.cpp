#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

template<typename T>
void analyze_precision(const std::string& type_name) {
    // Явно использовать литералы типа T
    T one = static_cast<T>(1.0);
    T two = static_cast<T>(2.0);
    T epsilon = one;
    int mantissa_bits = 0;

    // Найдём машинное эпсилон (ε)
    while (one + epsilon / two != one) {
        epsilon /= two;
        mantissa_bits++;
    }

    std::cout << "Тип: " << type_name << std::endl;
    std::cout << "Машинное эпсилон (ε): " << std::setprecision(20) << epsilon << std::endl;
    std::cout << "Число битов мантиссы: " << mantissa_bits << std::endl;
    std::cout << "Минимальная степень: " << std::numeric_limits<T>::min_exponent << std::endl;
    std::cout << "Максимальная степень: " << std::numeric_limits<T>::max_exponent << std::endl;

    // Сравнение значений
    T half_eps = epsilon / two;
    std::cout << "\nСравнение значений:" << std::endl;
    std::cout << "1              = " << one << std::endl;
    std::cout << "1 + ε/2        = " << one + half_eps << std::endl;
    std::cout << "1 + ε          = " << one + epsilon << std::endl;
    std::cout << "1 + ε + ε/2    = " << one + epsilon + half_eps << std::endl;
    std::cout << "-----------------------------------\n" << std::endl;
}

int main() {
    analyze_precision<float>("float");
    analyze_precision<double>("double");
    return 0;
}
