import matplotlib.pyplot as plt
import numpy as np

x = np.array([2, 3, 4, 5, 6])
y1 = np.array([2.5, 3.47, 4.24, 5.29, 5.9])
y2 = np.array([2.51, 3.79, 4.58, 5.6, 6.5])
linear = np.array([2, 3, 4, 5, 6])

fig, ax = plt.subplots()

plt.bar(linear - 0.2, linear, width=0.2, label='Linear speedup', color='black')
plt.bar(x, y1, width=0.2, label='N = 10^7')
plt.bar(x + 0.2, y2, width=0.2, label='N = 10^8')

plt.xlabel('Number of threads')
plt.ylabel('Speedup')
plt.title('Monte-Carlo method')

ax.legend()

fig.savefig('chart.png', dpi=300)
