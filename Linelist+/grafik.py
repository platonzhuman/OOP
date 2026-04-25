import matplotlib.pyplot as plt
import numpy as np

# читаем данные из файла ! ! !
data = np.loadtxt('result.csv', delimiter=',', skiprows=1)  # пропускаем первую строку с k
n = data[:, 0].astype(int)               # это N
time_linelist = data[:, 1]               # это время :)

# читаем k из первой строки
with open('result.csv', 'r') as f:
    first_line = f.readline().strip()
    k = int(first_line.split(',')[1])


time_array = np.array([0.001498, 0.035686, 0.113774, 1.69566, 8.54363, 160.82, 520.498])

# помогающие линии для асимптотик
k_plot = np.linspace(0, 1_000_000, 100)
o_n = (time_linelist[-1] / n[-1]) * k_plot
o_n2 = (time_linelist[-1] / (n[-1]**2)) * (k_plot**2)

# построение графиков
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

ax1.plot(n, time_linelist, 'o-', label=f'LineList (k={k})', color='tab:blue', linewidth=2)
ax1.plot(k_plot, o_n, '--', label='O(N)', color='tab:orange')
ax1.plot(k_plot, o_n2, ':', label='O(N²)', color='tab:green')
ax1.set_title('Зависимость времени от N (LineList)')
ax1.set_xlabel('N')
ax1.set_ylabel('Время (сек)')
ax1.grid(True)
ax1.legend()

ax2.loglog(n, time_linelist, 'o-', label=f'LineList (k={k})', color='tab:blue', linewidth=2)
ax2.loglog(n, time_array, 's-', label='Array (пример)', color='tab:red', linewidth=2)
ax2.set_title('Сравнение двух реализаций')
ax2.set_xlabel('N')
ax2.set_ylabel('Время (сек)')
ax2.grid(True, which='both', linestyle='--', linewidth=0.5)
ax2.legend()

plt.tight_layout()
plt.show()
