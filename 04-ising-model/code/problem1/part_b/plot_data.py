import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# 1. Read the CSV file
# Ensure the filename matches what you wrote in your Rust program
df = pd.read_csv("./integral_error.csv")

# 2. Calculate log10 of iterations
# We create a new column for the X-axis data
df["log10_iteration"] = np.log10(df["iteration"])

# 3. Create the plot
plt.figure(figsize=(10, 6))

# Plot x = log10(iteration), y = ln_error
plt.plot(
    df["log10_iteration"],
    df["ln_error"],
    label="Approximation Error",
    color="blue",
    linewidth=1,
)

# 4. Formatting
plt.title("Integral Approximation Error Convergence")
plt.xlabel(r"$\log_{10}(\text{Iteration})$")
plt.ylabel(r"$\ln(\text{Error})$")
plt.grid(True, which="both", linestyle="--", alpha=0.7)
plt.legend()

# 5. Save and Show
plt.savefig("convergence_plot.png", dpi=300)
plt.show()
