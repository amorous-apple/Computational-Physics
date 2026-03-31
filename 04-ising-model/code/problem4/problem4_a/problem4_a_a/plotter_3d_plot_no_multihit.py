import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import os

# 1. Configuration
data_dir = "./data_thermalization"
output_dir = "./plots"
os.makedirs(output_dir, exist_ok=True)

# The 11 beta values you generated in Rust (0.0 to 1.0)
betas = [b / 10.0 for b in range(11)]

# A list to store the dataframes for each beta
data_frames_list = []

print("Loading and combining data for all beta values...")

for beta in betas:
    filename = f"{data_dir}/thermalization_beta{beta}.csv"

    try:
        # Load the raw data
        df_raw = pd.read_csv(filename)
    except FileNotFoundError:
        print(f"Could not find {filename}. Skipping...")
        continue

    # --- CRITICAL FILTER ---
    # Since we know N_try=1 is optimal, we ONLY take data where n_try_index == 1
    # This automatically gives us the 801 thinned data points for this beta!
    df_filtered = df_raw[df_raw["n_try_index"] == 1].copy()

    # Store this filtered dataframe
    data_frames_list.append(df_filtered)

# Combine all 11 filtered dataframes into one single massive dataframe
if not data_frames_list:
    print("No data was found. Program exiting.")
    exit()

master_df = pd.concat(data_frames_list, ignore_index=True)

print("Data combined successfully. Reshaping and plotting...")

# 2. Reshape the single master dataframe into a 2D grid for the surface plot
# We pivot so that X = beta_val, Y = sweep_index, and Z = energy_density
pivot_df = master_df.pivot(
    index="sweep_index", columns="beta_val", values="energy_density"
)

# Extract the unique axis values and the Z grid from the pivoted dataframe
sweep_indices = pivot_df.index
beta_vals = pivot_df.columns
Z = pivot_df.values

# Create the mathematical meshgrid for the plot
X, Y = np.meshgrid(beta_vals, sweep_indices)

# 3. Set up the 3D plot
fig = plt.figure(figsize=(14, 10))
ax = fig.add_subplot(111, projection="3d")

# Plot the single combined surface using a nice colormap
surf = ax.plot_surface(X, Y, Z, cmap="viridis", edgecolor="none", alpha=0.9)

# 4. Labels and Titles
ax.set_title("Energy Density Convergence vs. Beta and Sweeps (N_try=1)", fontsize=18)
ax.set_xlabel(r"Inverse Temperature ($\beta$)", fontsize=14, labelpad=15)
ax.set_ylabel("Sweep Index (Time)", fontsize=14, labelpad=15)
ax.set_zlabel(r"Energy Density ($\epsilon$)", fontsize=14, labelpad=15)

# Add a color bar map
fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10, pad=0.1, label="Energy Density")

# Adjust the default viewing angle for a good perspective of both convergence and beta dependencies
ax.view_init(elev=30, azim=45)

# 5. Save the final single plot
savename = f"{output_dir}/plot_multibeta_thermalization.png"
plt.savefig(savename, dpi=300, bbox_inches="tight")
plt.close()

print(f"Final combined plot generated successfully at: {savename}")
