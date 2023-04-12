import matplotlib.pyplot as plt
import numpy as np

y = np.array([1.996, 2.963, 3.919, 4.801, 5.225])
linear = np.array([2, 3, 4, 5, 6])

fig, ax = plt.subplots()

plt.bar(linear - 0.1, linear, width=0.2, label='Linear speedup', color='black')
plt.bar(linear + 0.1, y, width=0.2, label='eps=E-5')

plt.xlabel('Number of threads')
plt.ylabel('Speedup')
plt.title('Midpoint rule')

ax.legend()

fig.savefig('chart.png', dpi=300)
