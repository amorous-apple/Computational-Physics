import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


M = 64          
L = 8           

dateien = {
    0.05:  "./code/data/activity_005_new.csv",
    0.125: "./code/data/activity_0125_new.csv",
    0.25:  "./code/data/activity_025_new.csv",
    0.56:  "./code/data/activity_056_new.csv",
    0.84:  "./code/data/activity_084_new.csv",
    1.10:  "./code/data/activity_11_new.csv",
    1.15:  "./code/data/activity_115_new.csv",
    1.50:  "./code/data/activity_15_new.csv",
}


# Anzahl der ersten Zeilen, die verworfen werden
skip_rows = 3


def standardfehler(x):
    """
    Fehler des Mittelwertes = Stichproben-Stdabw / sqrt(n)
    """
    x = np.asarray(x, dtype=float)
    n = len(x)
    if n < 2:
        return np.nan
    s = np.std(x, ddof=1)
    return s / np.sqrt(n)

def lade_daten(csv_datei, skip_rows=0):
    
    df = pd.read_csv(
        csv_datei,
        header=None,
        names=["step", "N", "N+", "N-"]
    )

    if skip_rows > 0:
        df = df.iloc[skip_rows:].copy()
    
    return df

def berechne_observablen(df, M, L):
    df = df.copy()

    # Packungsdichte eta = L*N / M^2
    df["eta"] = L * df["N"] / (M**2)

    # Ordnungparameter S, nur falls N > 0
    df["S"] = 0.0
    maske = df["N"] > 0
    df.loc[maske, "S"] = (df.loc[maske, "N+"] - df.loc[maske, "N-"]) / df.loc[maske, "N"]

    # Absolutwert
    df["absS"] = df["S"].abs()

    return df


ergebnisse = []

for z, datei in dateien.items():
    df = lade_daten(
        datei,
        skip_rows=skip_rows,
    )

    df = berechne_observablen(df, M=M, L=L)

    eta_mean = df["eta"].mean()
    eta_std = df["eta"].std(ddof=1)
    eta_sem = standardfehler(df["eta"])

    absS_mean = df["absS"].mean()
    absS_std = df["absS"].std(ddof=1)
    absS_sem = standardfehler(df["absS"])

    ergebnisse.append({
        "z": z,
        "n": len(df),
        "eta_mean": eta_mean,
        "eta_std": eta_std,
        "eta_sem": eta_sem,
        "absS_mean": absS_mean,
        "absS_std": absS_std,
        "absS_sem": absS_sem,
    })

erg = pd.DataFrame(ergebnisse)
erg = erg.sort_values("z").reset_index(drop=True)

print(erg)

# PLOT

plt.figure(figsize=(8, 6))

plt.errorbar(
    erg["eta_mean"],
    erg["absS_mean"],
    xerr=erg["eta_sem"],
    yerr=erg["absS_sem"],
    fmt="o",
    capsize=4
)

plt.xlabel(r"Dichte $\eta$")
plt.ylabel(r"Ordnungsparameter $|S|$")
plt.title(r"Ordnungsparameter $|S|$ in Abhängigkeit der Dichte")
plt.grid(True, alpha=0.5)
plt.tight_layout()

plt.savefig("./code/data/ordnung_vs_dichte.png", dpi=300)
