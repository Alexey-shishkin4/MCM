import numpy as np
import matplotlib.pyplot as plt

# Функция Рунге
def f(x):
    return 1 / (1 + 25 * x**2)

# Узлы Чебышёва на [-1, 1]
def chebyshev_nodes(n):
    return np.cos((2 * np.arange(1, n + 1) - 1) / (2 * n) * np.pi)

# Равномерные узлы
def uniform_nodes(n):
    return np.linspace(-1, 1, n)

# Интерполяционный полином через многочлен Лагранжа
def interpolate(x_nodes, y_nodes, x_eval):
    n = len(x_nodes)
    P = np.zeros_like(x_eval)
    for i in range(n):
        L = np.ones_like(x_eval)
        for j in range(n):
            if i != j:
                L *= (x_eval - x_nodes[j]) / (x_nodes[i] - x_nodes[j])
        P += y_nodes[i] * L
    return P

# Точки для построения
x_dense = np.linspace(-1, 1, 1000)
f_dense = f(x_dense)

fig, axs = plt.subplots(2, 2, figsize=(14, 10))

# --- Равномерные узлы ---
for n in range(3, 11):
    x_nodes = uniform_nodes(n)
    y_nodes = f(x_nodes)
    p_vals = interpolate(x_nodes, y_nodes, x_dense)

    # Верхний левый график: интерполяция
    axs[0, 0].plot(x_dense, p_vals, label=f"n={n}")
    # Нижний левый график: ошибка
    axs[1, 0].plot(x_dense, np.abs(p_vals - f_dense), label=f"n={n}")

axs[0, 0].plot(x_dense, f_dense, 'k--', linewidth=2, label="f(x)")
axs[0, 0].set_title("Интерполяция на равномерных узлах")
axs[0, 0].set_xlabel("x")
axs[0, 0].set_ylabel("Pₙ(x)")
axs[0, 0].legend()
axs[0, 0].grid()

axs[1, 0].set_title("Ошибка |Pₙ(x) - f(x)| (равномерные узлы)")
axs[1, 0].set_xlabel("x")
axs[1, 0].set_ylabel("Ошибка")
axs[1, 0].set_yscale("log")
axs[1, 0].legend()
axs[1, 0].grid()

# --- Узлы Чебышёва ---
for n in range(3, 11):
    x_nodes = chebyshev_nodes(n)
    y_nodes = f(x_nodes)
    p_vals = interpolate(x_nodes, y_nodes, x_dense)

    # Верхний правый график: интерполяция
    axs[0, 1].plot(x_dense, p_vals, label=f"n={n}")
    # Нижний правый график: ошибка
    axs[1, 1].plot(x_dense, np.abs(p_vals - f_dense), label=f"n={n}")

axs[0, 1].plot(x_dense, f_dense, 'k--', linewidth=2, label="f(x)")
axs[0, 1].set_title("Интерполяция на узлах Чебышёва")
axs[0, 1].set_xlabel("x")
axs[0, 1].set_ylabel("Pₙ(x)")
axs[0, 1].legend()
axs[0, 1].grid()

axs[1, 1].set_title("Ошибка |Pₙ(x) - f(x)| (узлы Чебышёва)")
axs[1, 1].set_xlabel("x")
axs[1, 1].set_ylabel("Ошибка")
axs[1, 1].set_yscale("log")
axs[1, 1].legend()
axs[1, 1].grid()

plt.tight_layout()
plt.show()
