import pandas as pd
import matplotlib.pyplot as plt
import os

# --- 1. CONFIGURATION ---
# Match these to the variables you used in your Rust main file
L = 128
beta = 0.7
data_dir = "./data"

# The filename string matches your Rust format exactly
filename = f"{data_dir}/hysteresis_L{L}_Beta{beta}.csv"

print(f"Loading hysteresis data from {filename}...")
try:
    df = pd.read_csv(filename)
except FileNotFoundError:
    print(f"Error: Could not find {filename}. Please check the file path.")
    exit()

# --- 2. SET UP THE FIGURE ---
fig, ax = plt.subplots(figsize=(10, 8))

# --- 3. PLOT THE HYSTERESIS LOOP ---
# We use a simple line plot. Because the data was recorded sequentially
# (+1.0 to -1.0, then back to +1.0), it will draw the loop naturally!
ax.plot(
    df["h_value"],
    df["magnetization"],
    color="crimson",
    linewidth=2.5,
    label=rf"Simulation path ($\beta={beta}$)",
)

# Add solid black lines at x=0 and y=0 to clearly show the origin
ax.axhline(y=0, color="black", linestyle="-", linewidth=1)
ax.axvline(x=0, color="black", linestyle="-", linewidth=1)

# --- 4. FORMATTING ---
ax.set_title(
    rf"Magnetic Hysteresis of the 2D Ising Model ($L={L}$)", fontsize=18, pad=15
)
ax.set_xlabel(r"External Magnetic Field ($h$)", fontsize=14, labelpad=10)
ax.set_ylabel(r"Magnetization ($\langle m \rangle$)", fontsize=14, labelpad=10)

# Lock the axes slightly past 1.0 so the data doesn't touch the edges of the image
ax.set_xlim([-1.1, 1.1])
ax.set_ylim([-1.1, 1.1])

ax.grid(True, linestyle="--", alpha=0.6)
ax.legend(loc="upper left", fontsize=12)

# --- 5. FINALIZE AND SAVE ---
plt.tight_layout()

output_dir = "./plots"
os.makedirs(output_dir, exist_ok=True)
savename = f"{output_dir}/plot_hysteresis_L{L}_Beta{beta}.png"
plt.savefig(savename, dpi=300, bbox_inches="tight")
plt.close()

print(f"Beautiful hysteresis plot generated successfully at: {savename}")
