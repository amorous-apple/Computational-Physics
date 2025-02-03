import matplotlib.pyplot as plt
import pandas as pd
import os

headers = ['t','J','E'] 
bodies = ['2body','3body']
integrators = ['euler','eulercrom','hermite','hermite_it','velver'] 
timesteps = ['0.01','0.5'] #technically omitting one 0.1 hermite

for b in bodies:
    for i in integrators:
        for t in timesteps:            
            try:
                data = pd.read_csv(f"./code/simulation/sim_data/data_calc/{b}_{i}_{t}_calc.csv",names=headers, skiprows=0, skipfooter=0, engine='python')
                df = pd.DataFrame(data)
                for h in headers[1:]:
                    df.plot(x='t', y=f'{h}', xlabel="time", ylabel=f"{h}", title=f"{b}_{i}_{t}_{h}", legend=False)
                    plt.savefig(f"./code/simulation/sim_data/data_calc/plots/{b}_{i}_{t}_{h}.png")
                    plt.close()
            except:
                print('you might be in the wrong wd, try executing in 01-nbody.')
                print('you are currently in')
                print(os.getcwd()) #tells you in which working directory you are. It should be "06-stiff_rods"

#data = pd.read_csv("//wsl.localhost/Ubuntu/home/noah/CP-Praktikum/Computational-Physics/01-nbody/code/simulation/sim_data/data_calc/plots/plot1.csv",names=headers, skiprows=0, skipfooter=0, engine='python')
