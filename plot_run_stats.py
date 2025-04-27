import numpy as np
import matplotlib.pyplot as plt

# Load data
data = np.loadtxt('run.stats')

# Unpack columns
generation = data[:, 0]
avg_fitness = data[:, 1]
best_fitness = data[:, 2]
best_program = data[:, 3]
avg_program_size = data[:, 4]
smallest_program_size = data[:, 5]
largest_program_size = data[:, 6]

# Create figure and axes
fig, axs = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

# Plot fitnesses
axs[0].plot(generation, avg_fitness, label='Average Fitness', marker='o')
axs[0].plot(generation, best_fitness, label='Best Fitness', marker='s')
axs[0].set_ylabel('Fitness')
axs[0].legend()
axs[0].grid(True)
axs[0].set_title('Fitness over Generations')

# Plot program sizes
axs[1].plot(generation, avg_program_size, label='Average Program Size', marker='o')
axs[1].plot(generation, smallest_program_size, label='Smallest Program Size', marker='^')
axs[1].plot(generation, largest_program_size, label='Largest Program Size', marker='v')
axs[1].set_xlabel('Generation')
axs[1].set_ylabel('Program Size')
axs[1].legend()
axs[1].grid(True)
axs[1].set_title('Program Size over Generations')

plt.tight_layout()
plt.savefig("run.png")