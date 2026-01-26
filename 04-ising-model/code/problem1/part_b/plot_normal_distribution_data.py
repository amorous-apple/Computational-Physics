# Plotting the data from ./normal_distribution.csv to verify correctness

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# 1. Load the data
# Assuming the file is in the same directory and named 'gaussian_data.csv'
df = pd.read_csv("./normal_distribution.csv")

# 2. Set up the plot
plt.figure(figsize=(10, 6))

# 3. Create the Histogram
# bins=50: Splits the data into 50 buckets
# density=True: Normalizes the height so the total area is 1 (crucial for comparing to the curve)
plt.hist(
    df["random_num"],
    bins=50,
    density=True,
    alpha=0.6,
    color="skyblue",
    edgecolor="black",
    label="MC Samples",
)

# 4. Overlay the Theoretical Normal Distribution
xmin, xmax = plt.xlim()
x = np.linspace(xmin, xmax, 100)
p = (1 / np.sqrt(2 * np.pi)) * np.exp(-0.5 * x**2)

plt.plot(x, p, "r", linewidth=2, label="Theoretical PDF")

# 5. Labels and Style
plt.title("Verification of Box-Muller Distribution")
plt.xlabel("Value (t)")
plt.ylabel("Probability Density")
plt.legend()
plt.grid(True, alpha=0.3)

# 6. Show the plot
plt.show()
