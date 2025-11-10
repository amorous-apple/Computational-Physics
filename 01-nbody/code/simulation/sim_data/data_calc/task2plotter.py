import matplotlib.pyplot as plt
import pandas as pd
import os

# --- MODIFICATION ---
# These are the *constant* headers for ALL files
# 'a' is for the semi-major axis
plot_headers = ["t", "J", "E", "a"]

bodies = ["2body", "3body", "100body", "1kbody"]
integrators = ["euler", "eulercrom", "velver", "hermite", "hermite_it", "heun", "rk4"]
timesteps = ["0.01", "0.05", "0.1", "0.5"]

# Create the plots directory if it doesn't exist
os.makedirs("./plots", exist_ok=True)

# 1. Loop over the main plot GROUPS (body and timestep)
for b in bodies:
    for t in timesteps:
        # --- MODIFICATION ---
        # Define which quantities to plot based on body type
        if b == "2body":
            # For 2body, we want to plot all three
            quantities_to_plot = ["J", "E", "a"]
        else:
            # For all other systems, we only plot Energy
            quantities_to_plot = ["E"]
        # --- MODIFICATION END ---

        # 2. Loop over the *selected* physical quantities
        for h in quantities_to_plot:  # <-- This list is now conditional
            fig, ax = plt.subplots(figsize=(10, 6))
            print(f"--- Creating plot for: {b}, {t}, {h} ---")

            # 3. Loop over the integrators to add them to the plot
            for i in integrators:
                try:
                    filepath = f"./{b}_{i}_{t}_calc.csv"

                    # --- MODIFICATION ---
                    # Always use the 4-column plot_headers
                    data = pd.read_csv(
                        filepath,
                        names=plot_headers,  # <-- Now always correct
                        skiprows=0,
                        skipfooter=0,
                        engine="python",
                    )
                    df = pd.DataFrame(data)

                    # Plot the selected column (e.g., 'E')
                    ax.plot(df["t"], df[h], label=i)

                except FileNotFoundError:
                    print(
                        f"  > File not found: {filepath}. Skipping {i} for this plot."
                    )
                except Exception as e:
                    print(f"  > An error occurred reading {filepath}: {e}")

            # --- CONFIGURE AND SAVE THE COMBINED PLOT ---

            # 1. Set the correct Y-label and Title
            if h == "E":
                plot_ylabel = r"$log|(E - E_0) / E_0|$"
                plot_title = f"Integrator Comparison: Energy, {b}, dt={t}"
            elif h == "J":
                plot_ylabel = r"$log|e - e_0|$"
                plot_title = f"Integrator Comparison: Runge-Lenz Vector, {b}, dt={t}"
            # --- MODIFICATION ---
            elif h == "a":  # Changed from "semi" to "a"
                plot_ylabel = r"$log|(a - a_0) / a_0|$"
                plot_title = f"Integrator Comparison: Semi-Major Axis, {b}, dt={t}"

            # 2. Set labels, title, and add the legend
            ax.set_xlabel("time")
            ax.set_ylabel(plot_ylabel)
            ax.set_title(plot_title)

            ax.legend()
            ax.grid(True, linestyle="--", alpha=0.7)

            # 3. Save the combined figure
            save_filename = f"./plots/{b}_{t}_{h}_comparison.png"
            plt.savefig(
                save_filename,
                dpi=300,
                bbox_inches="tight",
            )

            # 4. Close the figure
            plt.close(fig)

print("\nAll comparison plots created.")
