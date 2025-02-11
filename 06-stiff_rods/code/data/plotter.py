import matplotlib.pyplot as plt
import pandas as pd
import os
print(os.getcwd()) #tells you in working directory you are in case you need to change read_csv and savefig

headers = ['t','N', 'N1', 'N2'] 
data = pd.read_csv("./plot1.csv",names=headers, skiprows=0, skipfooter=0, engine='python')

df = pd.DataFrame(data)

df.plot(x='t', xlabel="xlabel", ylabel="ylabel", title="title")
plt.savefig("./plot2.png")
