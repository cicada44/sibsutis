import matplotlib.pyplot as plt

# Data
x = [2, 3, 4, 5, 6]
y = [2.344, 3.268, 4.277, 5.045, 6.021]

# Create a bar chart
plt.bar(x, y)

# Set the y-axis limits
plt.ylim([0, max(y) + 2])

# Add labels and title
plt.xlabel('Number of threads')
plt.ylabel('Speedup')
plt.title('Monte-Carlo method, N=10^7')

# Display the chart
plt.show()