import matplotlib.pyplot as plt

# Data
x = [2, 3, 4, 5, 6]
y = [2.23, 3.309, 4.303, 5.059, 6.174]

# Create a bar chart
plt.bar(x, y)

# Set the y-axis limits
plt.ylim([0, max(y) + 2])

# Add labels and title
plt.xlabel('Number of threads')
plt.ylabel('Speedup')
plt.title('Monte-Carlo method, N=10^8')

# Display the chart
plt.show()