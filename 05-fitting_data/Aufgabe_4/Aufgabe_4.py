import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt

def N(t,N0,N1,N2,lambda1,lambda2):
    return N0 + N1*np.exp(-lambda1*t) + N2*np.exp(-lambda2*t)

def chi2(params):
    model = N(data[:,0], *params)
    residuals = data[:,1] - model
    return np.sum((residuals / sigma)**2)

data = np.loadtxt(r"./Aufgabe_4/Agdecay.dat", skiprows=3)
sigma = np.sqrt(data[:,1])
t_fit = np.linspace(0,120,200)

initial_guess = np.array([0.0, 800.0, 100.0, 0.1, 0.01])

result_simplex = minimize(chi2,initial_guess,method = 'Nelder-Mead')
N_simplex = N(t_fit,*result_simplex.x)
result_cg = minimize(chi2,initial_guess,method = 'CG')
N_cg = N(t_fit,*result_cg.x)

plt.figure("Aufgabe_4", figsize=(10,8))
plt.plot(data[:,0], data[:,1], "x", label="Data", color="b")
plt.plot(t_fit, N_simplex, label=fr'Simplex, $\chi^2$ = {chi2(result_simplex.x):.2f}',color = (0.301, 0.886, 0.0),lw=2)
plt.plot(t_fit, N_cg, label=fr'Conjugate Gradient $\chi^2$ = {chi2(result_cg.x):.2f}', c = 'r',lw=2)
plt.xlabel("Zeit [s]")
plt.ylabel("N")
plt.title("Zerfall von Ag, Simplex-Algorithmus vs. Conjugate Gradient Methode")
plt.legend()
plt.grid()
plt.savefig(r"./Aufgabe_4/Zerfall.png")

with open(r'./Aufgabe_4/parameter.txt',"w") as file:
    file.write('Simplex-Algorithmus:\n')
    file.write(f'N0: {result_simplex.x[0]}\n')
    file.write(f'N1: {result_simplex.x[1]}\n')
    file.write(f'N2: {result_simplex.x[2]}\n')
    file.write(f'lambda1: {result_simplex.x[3]}\n')
    file.write(f'lambda2: {result_simplex.x[4]}')
    file.write('\n\n')
    file.write('Conjugate Gradient:\n')
    file.write(f'N0: {result_cg.x[0]}\n')
    file.write(f'N1: {result_cg.x[1]}\n')
    file.write(f'N2: {result_cg.x[2]}\n')
    file.write(f'lambda1: {result_cg.x[3]}\n')
    file.write(f'lambda2: {result_cg.x[4]}')
    file.close()