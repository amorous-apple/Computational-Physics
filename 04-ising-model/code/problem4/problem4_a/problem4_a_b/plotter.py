import pandas as pd
import matplotlib.pyplot as plt
import os

# --- 1. CONFIGURATION ---
data_file = "./data/task_3b_data.csv"
output_dir = "./plots"
os.makedirs(output_dir, exist_ok=True)

print(f"Loading data from {data_file}...")
try:
    # skipinitialspace=True handles the spaces we put after the commas in the Rust writeln!
    df = pd.read_csv(data_file, skipinitialspace=True)
except FileNotFoundError:
    print(f"Error: Could not find {data_file}. Please check the file path.")
    exit()

# Sort the dataframe by L to ensure the lines draw strictly left-to-right
df = df.sort_values(by="L")

# --- 2. SET UP THE FIGURE ---
# 3 stacked subplots sharing the X-axis
fig, (ax_e, ax_m, ax_m2) = plt.subplots(3, 1, figsize=(10, 12), sharex=True)
fig.suptitle(
    r"Finite Size Scaling at Critical Temperature ($\beta \approx 0.440687$)",
    fontsize=18,
    y=0.95,
)

# --- 3. PLOT 1: ENERGY DENSITY ---
ax_e.plot(
    df["L"],
    df["energy_density"],
    marker="o",
    color="blue",
    linestyle="-",
    markersize=8,
    linewidth=2,
)
ax_e.set_ylabel(r"Energy Density ($\epsilon$)", fontsize=14)
ax_e.set_title("Internal Energy vs. Grid Size", fontsize=14)
ax_e.grid(True, linestyle="--", alpha=0.6)

# --- 4. PLOT 2: ABSOLUTE MAGNETIZATION ---
ax_m.plot(
    df["L"],
    df["m_abs"],
    marker="s",
    color="green",
    linestyle="-",
    markersize=8,
    linewidth=2,
)
ax_m.set_ylabel(r"$\langle |m| \rangle$", fontsize=14)
ax_m.set_title("Absolute Magnetization vs. Grid Size", fontsize=14)
ax_m.grid(True, linestyle="--", alpha=0.6)

# --- 5. PLOT 3: SQUARED MAGNETIZATION ---
ax_m2.plot(
    df["L"],
    df["m_sqr"],
    marker="^",
    color="purple",
    linestyle="-",
    markersize=8,
    linewidth=2,
)
ax_m2.set_xlabel("Grid Size ($L$)", fontsize=14)
ax_m2.set_ylabel(r"$\langle m^2 \rangle$", fontsize=14)
ax_m2.set_title("Squared Magnetization vs. Grid Size", fontsize=14)
ax_m2.grid(True, linestyle="--", alpha=0.6)

# Force the X-axis to display ticks exactly at our simulated L values
ax_m2.set_xticks(df["L"])

# --- 6. FINALIZE AND SAVE ---
plt.tight_layout()
savename = f"{output_dir}/plot_task3b_finite_size.png"
plt.savefig(savename, dpi=300, bbox_inches="tight")
plt.close()

print(f"Finite size scaling plot generated successfully at: {savename}")
