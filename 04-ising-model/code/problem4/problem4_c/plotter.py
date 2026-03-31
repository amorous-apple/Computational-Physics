import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

# --- 1. CONFIGURATION ---
L = 128  # Ensure this matches your simulation
data_dir = "./data"
output_dir = "./plots"
filename = f"{data_dir}/ising_L{L}.csv"

os.makedirs(output_dir, exist_ok=True)

print(f"Loading phase diagram data from {filename}...")
try:
    df = pd.read_csv(filename)
except FileNotFoundError:
    print(f"Error: Could not find {filename}. Please check the file path.")
    exit()

# --- 2. RESHAPE THE DATA FOR 3D PLOTTING ---
# Pivot the flat CSV into 2D matrices.
# Rows become 'h', Columns become 'beta', Values are the observables.
grid_m = df.pivot(index="h_value", columns="beta_value", values="magnetization")
grid_m_abs = df.pivot(index="h_value", columns="beta_value", values="magnetization_abs")

# Extract the coordinate arrays and create the meshgrid for Matplotlib
X, Y = np.meshgrid(grid_m.columns.values, grid_m.index.values)
Z_m = grid_m.values
Z_m_abs = grid_m_abs.values

# --- 3. PLOT 1: SIGNED MAGNETIZATION <m> ---
print("Generating 3D surface for Signed Magnetization...")
fig1 = plt.figure(figsize=(12, 9))
ax1 = fig1.add_subplot(111, projection="3d")

# RdBu_r colormap is great for signed data: Red (+1), White (0), Blue (-1)
surf1 = ax1.plot_surface(
    X, Y, Z_m, cmap="magma", edgecolor="none", alpha=0.9, vmin=-1.0, vmax=1.0
)

ax1.set_title(
    rf"Signed Magnetization $\langle m \rangle$ ($L={L}$)", fontsize=18, pad=20
)
ax1.set_xlabel(r"Inverse Temp ($\beta$)", fontsize=12, labelpad=10)
ax1.set_ylabel(r"External Field ($h$)", fontsize=12, labelpad=10)
ax1.set_zlabel(r"$\langle m \rangle$", fontsize=12, labelpad=10)

# Set viewing angle (Elevation, Azimuth) to best see the transition
ax1.view_init(elev=25, azim=-125)
fig1.colorbar(
    surf1, ax=ax1, shrink=0.5, aspect=10, pad=0.1, label=r"$\langle m \rangle$"
)

savepath1 = f"{output_dir}/surface_3d_m_L{L}.png"
fig1.savefig(savepath1, dpi=300, bbox_inches="tight")
plt.close(fig1)

# --- 4. PLOT 2: ABSOLUTE MAGNETIZATION <|m|> ---
print("Generating 3D surface for Absolute Magnetization...")
fig2 = plt.figure(figsize=(12, 9))
ax2 = fig2.add_subplot(111, projection="3d")

# Magma colormap is great for absolute data: Dark (0) to Bright (1)
surf2 = ax2.plot_surface(
    X, Y, Z_m_abs, cmap="magma", edgecolor="none", alpha=0.9, vmin=0.0, vmax=1.0
)

ax2.set_title(
    rf"Absolute Magnetization $\langle |m| \rangle$ ($L={L}$)", fontsize=18, pad=20
)
ax2.set_xlabel(r"Inverse Temp ($\beta$)", fontsize=12, labelpad=10)
ax2.set_ylabel(r"External Field ($h$)", fontsize=12, labelpad=10)
ax2.set_zlabel(r"$\langle |m| \rangle$", fontsize=12, labelpad=10)

# Set viewing angle
ax2.view_init(elev=25, azim=-125)
fig2.colorbar(
    surf2, ax=ax2, shrink=0.5, aspect=10, pad=0.1, label=r"$\langle |m| \rangle$"
)

savepath2 = f"{output_dir}/surface_3d_m_abs_L{L}.png"
fig2.savefig(savepath2, dpi=300, bbox_inches="tight")
plt.close(fig2)

print(f"Success! Plots saved to:\n - {savepath1}\n - {savepath2}")
