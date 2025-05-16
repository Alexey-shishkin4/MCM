import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data = pd.read_csv("fractal_data.csv")
colors = {0: "red", 1: "green", 2: "blue"}

fig, ax = plt.subplots(figsize=(8, 8))
for root_id, group in data.groupby("root"):
    ax.scatter(group.x, group.y, c=colors.get(root_id, "black"), s=0.5, label=f"Корень {root_id + 1}")

ax.set_title("Фрактал Ньютона для z^3 - 1")
ax.set_xlabel("Re(z)")
ax.set_ylabel("Im(z)")
ax.legend()
plt.axis("equal")
plt.grid(True)
plt.show()
"""Если закрашивать каждую точку по тому, к какому корню она привела 
при применении метода Ньютона, получится цветной фрактал Ньютона."""
#1.2 -1.5

# 1) Считываем фрактальные данные
data = pd.read_csv("fractal_data.csv")

# 2) Выбираем первую точку из синей области (root==2)
pt = data[data['root'] == 2].iloc[20]
z0 = complex(pt.x, pt.y)
print(f"Начальное z0 из синей области: {z0}")

# 3) Реализуем метод Ньютона для z^3 = 1
def newton(z0, max_iter=20, eps=1e-6):
    zs = [z0]
    z = z0
    for i in range(max_iter):
        f  = z**3 - 1
        df = 3*z**2
        if abs(df) < eps:
            break
        z_new = z - f/df
        zs.append(z_new)
        if abs(z_new - z) < eps:
            break
        z = z_new
    return zs

# 4) Запускаем и печатаем все шаги
trajectory = newton(z0)
for i, z in enumerate(trajectory):
    print(f"  итерация {i:2d}: z = {z}")

# 5) Печатаем "истинный" корень из массива roots, к которому мы относили этот цвет
roots = [1, 
         np.exp(2j*np.pi/3), 
         np.exp(4j*np.pi/3)]
target_root = roots[2]
print(f"\nКорень, к которому ведёт сходимость (root_id=2): {target_root}")
print(f"Окончательное приближение: {trajectory[-1]}")
print(f"Погрешность: {abs(trajectory[-1] - target_root)}")
"""root[0] = (-0.5,-0.866025)
root[1] = (1,-3.0008e-14)
root[2] = (-0.5,0.866025)"""