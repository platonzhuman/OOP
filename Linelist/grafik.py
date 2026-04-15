import matplotlib.pyplot as plt
import numpy as np

n = np.array([1000, 5000, 10000, 50000, 100000, 500000, 1000000])
time_linelist = np.array([0.000017, 0.000081, 0.000165, 0.002170, 0.004966, 0.032751, 0.073244])
time_array = np.array([0.001498, 0.035686, 0.113774, 1.69566, 8.54363, 160.82, 520.498])

k = np.linspace(0, 1_000_000, 100)
o_n = (time_linelist[-1] / n[-1]) * k
o_n2 = (time_linelist[-1] / (n[-1]**2)) * (k**2)

ratio = time_array / time_linelist
kof = np.mean(ratio)
print(f"Среднее отношение time_array / time_linelist = {kof:.2f}")

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

ax1.plot(n, time_linelist, 'o-', label='LineList', color='tab:blue', linewidth=2)
ax1.plot(k, o_n, '--', label='O(N)', color='tab:orange')
ax1.plot(k, o_n2, ':', label='O(N²)', color='tab:green')
ax1.set_title('Зависимость времени от N (LineList)')
ax1.set_xlabel('N')
ax1.set_ylabel('Время (сек)')
ax1.grid(True)
ax1.legend()

ax2.loglog(n, time_linelist, 'o-', label='LineList', color='tab:blue', linewidth=2)
ax2.loglog(n, time_array, 's-', label='Array', color='tab:red', linewidth=2)
ax2.set_title('Сравнение двух реализаций')
ax2.set_xlabel('N')
ax2.set_ylabel('Время (сек)')
ax2.grid(True, which='both', linestyle='--', linewidth=0.5)
ax2.legend()



plt.tight_layout()
plt.show()