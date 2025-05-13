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