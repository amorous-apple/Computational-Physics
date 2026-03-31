import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import os

# Create a folder to save our generated plots
output_dir = "./plots"
os.makedirs(output_dir, exist_ok=True)

# The 11 beta values you generated in Rust (0.0 to 1.0)
betas = [b / 10.0 for b in range(11)]

for beta in betas:
    # 1. Load the data
    filename = f"./data_thermalization/thermalization_beta{beta}.csv"

    try:
        df = pd.read_csv(filename)
    except FileNotFoundError:
        print(f"Could not find {filename}. Skipping...")
        continue

    print(f"Plotting Beta = {beta}...")

    # 2. NO DOWNSAMPLING NEEDED (Rust already did it!)
    # 3. Reshape directly from the main dataframe
    pivot_df = df.pivot(
        index="n_try_index", columns="sweep_index", values="energy_density"
    )

    # Extract the grids
    X, Y = np.meshgrid(pivot_df.columns, pivot_df.index)
    Z = pivot_df.values

    # 4. Set up the 3D plot
    fig = plt.figure(figsize=(12, 8))
    ax = fig.add_subplot(111, projection="3d")

    # Plot the surface using a nice colormap (viridis is great for colorblindness and contrast)
    surf = ax.plot_surface(X, Y, Z, cmap="viridis", edgecolor="none", alpha=0.9)

    # 5. Labels and Titles
    ax.set_title(f"Thermalization at $\\beta = {beta}$", fontsize=16)
    ax.set_xlabel("Sweep Index (Time)", fontsize=12, labelpad=10)
    ax.set_ylabel("Multihits ($N_{try}$)", fontsize=12, labelpad=10)
    ax.set_zlabel("Energy Density ($\epsilon$)", fontsize=12, labelpad=10)

    # Add a color bar map
    fig.colorbar(surf, ax=ax, shrink=0.5, aspect=10, pad=0.1, label="Energy Density")

    # Adjust the viewing angle (Elevation, Azimuth)
    ax.view_init(elev=30, azim=-45)

    # 6. Save the plot instead of freezing the screen with 11 popups!
    savename = f"{output_dir}/plot_beta_{beta}.png"
    plt.savefig(savename, dpi=300, bbox_inches="tight")
    plt.close()  # Close the figure to free up memory

print("All plots generated successfully!")
