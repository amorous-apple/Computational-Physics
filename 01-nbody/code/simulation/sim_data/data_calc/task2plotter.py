import matplotlib.pyplot as plt
import pandas as pd
import os

headers = ["t", "J", "E"]
bodies = ["2body", "3body", "100body"]
integrators = ["euler", "eulercrom", "hermite", "velver"]
timesteps = ["0.01", "0.1", "0.5"]  # technically omitting one 0.1 hermite

for b in bodies:
    for i in integrators:
        for t in timesteps:
            try:
                data = pd.read_csv(
                    f"./{b}_{i}_{t}_calc.csv",
                    names=headers,
                    skiprows=0,
                    skipfooter=0,
                    engine="python",
                )
                df = pd.DataFrame(data)
                for h in headers[1:]:
                    df.plot(
                        x="t",
                        y=f"{h}",
                        xlabel="time",
                        ylabel=f"{h}",
                        title=f"{b}_{i}_{t}_{h}",
                        legend=False,
                    )
                    plt.savefig(
                        f"./plots/{b}_{i}_{t}_{h}.png",
                        dpi=300,
                        bbox_inches="tight",
                    )
                    plt.close()
            except:
                print("you might be in the wrong wd, try executing in /data_calc.")
                print("you are currently in")
                print(os.getcwd())
