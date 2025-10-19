import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

xmin = -1
xmax = 1
x = np.arange(-1, 1, 0.001)
a = 1 
# analytical solutions is just a shift proportional to a and t_max
def psi_0(x):
    return np.where(np.abs(x) <= 1/3, 1, 0)
def shift(x, t_max):
    d = a * t_max
    L = xmax - xmin
    return xmin + np.mod(x - d + xmax, L)

psi_analytic_t4 = psi_0(shift(x, 4.0))
psi_analytic_t400 = psi_0(shift(x, 400.0))


psi_N40_sigma08 = np.loadtxt(r"./output1/psi_N40.0_sigma0.8.txt", delimiter= ";")
xb_N40_simga08 = np.loadtxt(r"./output1/xb_N40.0_sigma0.8.txt", delimiter= ";")
psi_N40_sigma09 = np.loadtxt(r"./output1/psi_N40.0_sigma0.9.txt", delimiter= ";")
xb_N40_simga09 = np.loadtxt(r"./output1/xb_N40.0_sigma0.9.txt", delimiter= ";")
psi_N40_sigma10 = np.loadtxt(r"./output1/psi_N40.0_sigma1.0.txt", delimiter= ";")
xb_N40_simga10 = np.loadtxt(r"./output1/xb_N40.0_sigma1.0.txt", delimiter= ";")
psi_N40_sigma11 = np.loadtxt(r"./output1/psi_N40.0_sigma1.1.txt", delimiter= ";")
xb_N40_simga11 = np.loadtxt(r"./output1/xb_N40.0_sigma1.1.txt", delimiter= ";")

psi_N400_sigma08 = np.loadtxt(r"./output1/psi_N400.0_sigma0.8.txt", delimiter= ";")
xb_N400_simga08 = np.loadtxt(r"./output1/xb_N400.0_sigma0.8.txt", delimiter= ";")
psi_N400_sigma09 = np.loadtxt(r"./output1/psi_N400.0_sigma0.9.txt", delimiter= ";")
xb_N400_simga09 = np.loadtxt(r"./output1/xb_N400.0_sigma0.9.txt", delimiter= ";")

list_N40 = [(0.8, xb_N40_simga08, psi_N40_sigma08), (0.9,xb_N40_simga09,psi_N40_sigma09), (1.0,xb_N40_simga10,psi_N40_sigma10), (1.1,xb_N40_simga11,psi_N40_sigma11)]

for s, xb, psi in list_N40:
    plt.figure("extended_upwind_t4s_N40", figsize=(10, 8))
    plt.plot(xb[2:42], psi[2:42], label="extended upwind method")
    plt.plot(x, psi_analytic_t4, label="analytical solution")
    plt.xlabel("x")
    plt.ylabel(r"$\psi(x,t=4s)$")
    plt.title(r"40 gridpoints and $\sigma =$"+str(s))
    plt.grid()
    plt.legend()
    plt.savefig(f"./plots1/upwind_N40_sigma{s}.png")
    plt.close()

list_N400 = [(0.8, xb_N400_simga08, psi_N400_sigma08), (0.9,xb_N400_simga09,psi_N400_sigma09)] #, (1.0,xb_N400_simga10,psi_N400_sigma10), (1.1,xb_N400_simga11,psi_N400_sigma11)]

for s, xb, psi in list_N400:
    plt.figure("extended_upwind_t4s_N40", figsize=(10, 8))
    plt.plot(xb[2:402], psi[2:402], label="extended upwind method")
    plt.plot(x, psi_analytic_t4, label="analytical solution")
    plt.xlabel("x")
    plt.ylabel(r"$\psi(x,t=400s)$")
    plt.title(r"400 gridpoints and $\sigma =$"+str(s))
    plt.grid()
    plt.legend()
    plt.savefig(f"./plots1/upwind_N400_sigma{s}.png")
    plt.close()
