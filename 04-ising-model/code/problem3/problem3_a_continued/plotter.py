import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# --- 1. CONFIGURATION ---
# UPDATED: Pointing to the correct data folder
data_dir = "./data"
filename = f"{data_dir}/ising_L128.csv"
L = 128

# The exact analytical critical inverse temperature (Onsager solution)
beta_c = 0.5 * np.log(1 + np.sqrt(2))  # approx 0.440687

print(f"Loading data from {filename}...")
try:
    df = pd.read_csv(filename)
except FileNotFoundError:
    print(f"Error: Could not find {filename}. Please check the file path.")
    exit()

# --- 2. SET UP THE FIGURE ---
# We create 3 stacked subplots that share the same X-axis
fig, (ax_e, ax_m, ax_c) = plt.subplots(3, 1, figsize=(10, 12), sharex=True)
fig.suptitle(f"2D Ising Model Thermodynamics ($L = {L}$)", fontsize=18, y=0.95)

# --- 3. PLOT 1: ENERGY DENSITY ---
ax_e.plot(
    df["beta_vals"], df["energy_density"], label="Simulation", color="blue", linewidth=2
)
ax_e.plot(
    df["beta_vals"],
    df["anal_energy_density"],
    label="Analytical",
    color="black",
    linestyle="--",
    linewidth=2,
)
ax_e.axvline(
    x=beta_c,
    color="red",
    linestyle=":",
    linewidth=1.5,
    label=r"Critical $\beta_c \approx 0.44$",
)

ax_e.set_ylabel(r"Energy Density ($\epsilon$)", fontsize=14)
ax_e.set_title("Internal Energy", fontsize=14)
ax_e.grid(True, linestyle="--", alpha=0.6)
ax_e.legend(loc="best")

# --- 4. PLOT 2: MAGNETIZATION ---
# FIXED: Added the 'r' prefix to make it a raw string for \langle and \rangle!
ax_m.plot(
    df["beta_vals"],
    df["m"],
    label=r"Simulation $\langle |m| \rangle$",
    color="green",
    linewidth=2,
)
ax_m.plot(
    df["beta_vals"],
    df["anal_m"],
    label="Analytical (Onsager)",
    color="black",
    linestyle="--",
    linewidth=2,
)
ax_m.axvline(x=beta_c, color="red", linestyle=":", linewidth=1.5)

ax_m.set_ylabel(r"Magnetization ($|m|$)", fontsize=14)
ax_m.set_title("Spontaneous Magnetization", fontsize=14)
ax_m.grid(True, linestyle="--", alpha=0.6)
ax_m.legend(loc="best")

# --- 5. PLOT 3: SPECIFIC HEAT ---
ax_c.plot(
    df["beta_vals"],
    df["specific_heat"],
    label="Simulation (Variance)",
    color="purple",
    linewidth=2,
)
ax_c.axvline(x=beta_c, color="red", linestyle=":", linewidth=1.5)

ax_c.set_xlabel(r"Inverse Temperature ($\beta$)", fontsize=14)
ax_c.set_ylabel(r"Specific Heat ($c$)", fontsize=14)
ax_c.set_title("Specific Heat Capacity", fontsize=14)
ax_c.grid(True, linestyle="--", alpha=0.6)
ax_c.legend(loc="best")

# --- 6. FINALIZE AND SAVE ---
plt.tight_layout()

output_dir = "./plots"
os.makedirs(output_dir, exist_ok=True)
savename = f"{output_dir}/thermodynamics_L{L}.png"
plt.savefig(savename, dpi=300, bbox_inches="tight")
plt.close()

print(f"Beautiful thermodynamics plot generated successfully at: {savename}")
