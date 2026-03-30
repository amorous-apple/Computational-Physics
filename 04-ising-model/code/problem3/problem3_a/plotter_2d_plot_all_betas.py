import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import os

# 1. Configuration
data_dir = "./data_thermalization"
output_dir = "./plots"
os.makedirs(output_dir, exist_ok=True)

# The 11 beta values
betas = [b / 10.0 for b in range(1, 11)]

# Create a clean, wide 2D figure
fig, ax = plt.subplots(figsize=(12, 7))

# Get a colormap to create a gradient of colors for our 11 lines (viridis is excellent here)
colors = cm.viridis(np.linspace(0, 1, len(betas)))

print("Loading data and generating 2D plot...")

# 2. Loop through and plot each beta as a separate line
for idx, beta in enumerate(betas):
    filename = f"{data_dir}/thermalization_beta{beta}.csv"

    try:
        df_raw = pd.read_csv(filename)
    except FileNotFoundError:
        print(f"Could not find {filename}. Skipping...")
        continue

    # Filter to only use the single-hit data
    df_filtered = df_raw[df_raw["n_try_index"] == 1].copy()

    # Check if there is actually data to plot
    if df_filtered.empty:
        continue

    # Plot the line!
    # We use linewidth=1.5 for clarity, and alpha=0.8 so overlapping lines are slightly transparent
    ax.plot(
        df_filtered["sweep_index"],
        df_filtered["energy_density"],
        color=colors[idx],
        linewidth=1.5,
        alpha=0.8,
        label=rf"$\beta = {beta}$",
    )

# 3. Formatting the plot
ax.set_title("Energy Density Thermalization vs. Time (2D)", fontsize=16, pad=15)
ax.set_xlabel("Sweep Index (Time)", fontsize=14, labelpad=10)
ax.set_ylabel(r"Energy Density ($\epsilon$)", fontsize=14, labelpad=10)

# Add a grid to make it easier to trace the flatlines back to the y-axis
ax.grid(True, linestyle="--", alpha=0.6)

# Put the legend outside the plot so it doesn't cover up any data
ax.legend(title="Inverse Temp", bbox_to_anchor=(1.05, 1), loc="upper left", fontsize=11)

# Ensure everything fits nicely before saving
plt.tight_layout()

# 4. Save the plot
savename = f"{output_dir}/plot_2d_thermalization_lines.png"
plt.savefig(savename, dpi=300)
plt.close()

print(f"2D plot generated successfully at: {savename}")
