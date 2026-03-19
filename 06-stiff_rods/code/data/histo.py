import pandas as pd
import matplotlib.pyplot as plt

dateien = {
    0.56: "./code/data/long_056.csv",
    0.84: "./code/data/long_084.csv",
    1.10: "./code/data/long_11.csv",
}

fig, axes = plt.subplots(nrows=3, ncols=4, figsize=(12, 8))
fig.suptitle("Histogramme verschiedener z-Werte", fontsize=16)

for i, (z, datei) in enumerate(dateien.items()):
    df = pd.read_csv(datei, header=None, names=["step", "N", "N+", "N-"])
    df = df.iloc[100:].copy() # skips first 100 lines for thermalisation

    df["S"] = 0.0
    maske = df["N"] > 0
    df.loc[maske, "S"] = (df.loc[maske, "N+"] - df.loc[maske, "N-"]) / df.loc[maske, "N"]

    # Spalte 1: N
    axes[i, 0].hist(df["N"], bins=50, density=True)
    axes[i, 0].set_title("N")

    # Spalte 2: N+
    axes[i, 1].hist(df["N+"], bins=50, density=True)
    axes[i, 1].set_title("N+")

    # Spalte 3: N-
    axes[i, 2].hist(df["N-"], bins=50, density=True)
    axes[i, 2].set_title("N-")

    # Spalte 4: S
    axes[i, 3].hist(df["S"], bins=50, range=(-1, 1), density=True)
    axes[i, 3].set_title("S")

    # z-Beschriftung links an die Zeile
    axes[i, 0].set_ylabel(f"z = {z}", fontsize=16, rotation=90, labelpad=30)

plt.tight_layout(rect=[0.05, 0.03, 1, 0.95])

plt.savefig("./code/data/histogramme_z_grid.png", dpi=300)
