import matplotlib.pyplot as plt
import pandas as pd
import os

headers = ['t','N', 'N+', 'N-'] 
z = 0.56
c = '056'
try:
    data = pd.read_csv(f"./code/data/activity_{c}.csv",names=headers, skiprows=0, skipfooter=0, engine='python')
    df = pd.DataFrame(data)
    df.plot(x='t', xlabel="Anzahl der Schritte", ylabel="Anzahl der Stäbchen", title=f"Thermalisierung mit z={z}", figsize=(8, 5))
    plt.savefig(f"./code/data/plot{c}.png")
except:
    print('you might be in the wrong wd, try executing in 06-stiff_rods.')
    print('you are currently in')
    print(os.getcwd()) #tells you in which working directory you are. It should be "06-stiff_rods"
