import matplotlib.pyplot as plt
import pandas as pd
import os

headers = ['t','N', 'N1', 'N2'] 

try:
    data = pd.read_csv("./code/data/plot1.csv",names=headers, skiprows=0, skipfooter=0, engine='python')
    df = pd.DataFrame(data)
    df.plot(x='t', xlabel="xlabel", ylabel="ylabel", title="title")
    plt.savefig("./code/data/plot1.png")
except:
    print('you might be in the wrong wd, try executing in 06-stiff_rods.')
    print('you are currently in')
    print(os.getcwd()) #tells you in which working directory you are. It should be "06-stiff_rods"
