import matplotlib.pyplot as plt

# Data
x = [2, 3, 4, 5, 6]
y = [1.996, 2.963, 3.919, 4.801, 5.225]

# Create a bar chart
plt.bar(x, y)

# Set the y-axis limits
plt.ylim([0, max(y) + 2])

# Add labels and title
plt.xlabel('Number of threads')
plt.ylabel('Speedup')
plt.title('Midpoint rule')

# Display the chart
plt.show()