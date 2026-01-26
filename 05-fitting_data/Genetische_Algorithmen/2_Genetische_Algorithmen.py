from geneticalgorithm import geneticalgorithm as ga
import numpy as np
import matplotlib.pyplot as plt

def linear(x, a, b):
    return a*x + b

def chi2_lin(X):
    a, b = X
    chi2 = np.sum((data[:,1] - (data[:,0]*a + b))**2 / sigma**2)
    return chi2

def lin_sin(x, X):
    a, b = X[0], X[1]
    num_sin = (len(X) - 2) // 3
    if num_sin > 0:
        X_arr = np.array(X)
        c, d, e = X_arr[2::3], X_arr[3::3], X_arr[4::3]
        sin_sum = np.sum(c[:, None] * np.sin(2*np.pi*(x/d[:, None] + e[:, None])), axis=0)
    else:
        sin_sum = 0
    return a * x + b + sin_sum

def chi2_lin_sin(X):
    chi2 = np.sum((data[:,1] - lin_sin(data[:,0], X))**2 / sigma**2)
    return chi2

# Daten laden
data = np.loadtxt(r'./Genetische_Algorithmen/lichtkurve.dat')
sigma = 5


print("=== Aufgabe 2a: Linearer Fit ===")
varbound_lin = np.array([[0, 5], [8, 25]])

model_lin = ga(function=chi2_lin, dimension=2, variable_type='real', 
               variable_boundaries=varbound_lin, convergence_curve=True)
model_lin.run()

# Ergebnisse des linearen Fits
a_lin, b_lin = model_lin.output_dict['variable']
chi2_lin_result = model_lin.output_dict['function']

print(f"Linearer Fit: a = {a_lin:.6f}, b = {b_lin:.6f}")
print(f"chi2 = {chi2_lin_result:.2f}")

# Plot des linearen Fits
x_fit = np.linspace(data[:,0].min(), data[:,0].max(), 200)
#x_fit = np.linspace(0,100,200)
#a,b = 1.040524, 17.245337

plt.figure("Linearer Fit", figsize=(10, 8))
plt.scatter(data[:,0], data[:,1], label="Datenpunkte", marker='x', s=50)
plt.plot(x_fit, linear(x_fit, a_lin, b_lin), 
         label=f'Linearer Fit: $a = {a_lin:.3f}$, $b = {b_lin:.3f}$, $\chi^2 = {chi2_lin_result:.2f}$', 
         c='r', linewidth=2)
plt.xlabel("Zeit [s]")
plt.ylabel("Intensität")
plt.title("Lichtkurve mit linearem Fit")
plt.grid(True)
plt.legend()
plt.savefig('./Genetische_Algorithmen/plots2/linearer_fit.png', dpi=150)



print("\n=== Aufgabe 2b: Fits mit verschiedenen Sinusmoden ===")

results = []
max_moden = 5

for n_moden in range(1, max_moden + 1):
    print(f"\nFitting mit {n_moden} Sinusmoden")
    
    # Parametergrenzen: [a, b] + n_moden * [c, d, e]
    varbound = np.array([[0, 5], [15, 25]])  # a, b
    
    for i in range(n_moden):
        varbound = np.vstack([
            varbound,
            [0, 20],      # c: Amplitude
            [1, 50],      # d: Periode
            [0, 1]        # e: Phase
        ])
    
    # Genetischer Algorithmus
    algorithm_param = {
        'max_num_iteration': 500 if n_moden <= 3 else 1000,
        'population_size': 200 if n_moden <= 3 else 500,
        'mutation_probability': 0.2,
        'elit_ratio': 0.02,
        'crossover_probability': 0.5,
        'parents_portion': 0.4,
        'crossover_type': 'uniform',
        'max_iteration_without_improv': None
    }
    
    model = ga(function=chi2_lin_sin, 
               dimension=2 + 3*n_moden, 
               variable_type='real', 
               variable_boundaries=varbound,
               algorithm_parameters=algorithm_param,
               convergence_curve=True)
    model.run()
    
    X_best = model.output_dict['variable']
    chi2_best = model.output_dict['function']
    
    results.append({
        'n_moden': n_moden,
        'X': X_best,
        'chi2': chi2_best
    })
    
    print(f"  chi2 = {chi2_best:.2f}")
    print(f"  Parameter: a={X_best[0]:.3f}, b={X_best[1]:.3f}")


# Linearer Fit im ersten Plot
plt.figure("Linearer Fit2", figsize=(10, 8))
plt.scatter(data[:,0], data[:,1], label="Datenpunkte", marker='x', s=30, alpha=0.6)
plt.plot(x_fit, linear(x_fit, a_lin, b_lin), 'r-', linewidth=2,
         label=f'Linear: $\chi^2 = {chi2_lin_result:.2f}$')
plt.xlabel("Zeit [s]")
plt.ylabel("Intensität")
plt.title("Linearer Fit (0 Moden)")
plt.grid(True)
plt.legend()
plt.savefig('./Genetische_Algorithmen/plots2/fit_0_moden.png', dpi=150)

# Fits mit Sinusmoden

for i, result in enumerate(results):
    n_moden = result['n_moden']
    X = result['X']
    chi2 = result['chi2']
    
    plt.figure(f"Fit {n_moden} Moden", figsize=(10, 8))
    plt.scatter(data[:,0], data[:,1], label="Datenpunkte", marker='x', s=30, alpha=0.6)
    plt.plot(x_fit, lin_sin(x_fit, X), 'r-', linewidth=2,
            label=f'{n_moden} Mode(n): $\chi^2 = {chi2:.2f}$')
    plt.xlabel("Zeit [s]")
    plt.ylabel("Intensität")
    plt.title(f"Fit mit {n_moden} Sinusmode(n)")
    plt.grid(True)
    plt.legend()
    plt.savefig(f'./Genetische_Algorithmen/plots2/fit_{n_moden}_moden.png', dpi=150)

with open("./Genetische_Algorithmen/plots2/fit_parameters.tex", "w") as f:
    f.write("\\begin{table}[h]\n")
    f.write("\\centering\n")
    f.write("\\begin{tabular}{c c l}\n")
    f.write("\\hline\n")
    f.write("Moden & $\\chi^2$ & Parameter $[a, b, c_i, d_i, e_i]$ \\\\\n")
    f.write("\\hline\n")

    for r in results:
        n = r['n_moden']
        chi2 = r['chi2']
        X = r['X']

        params = ", ".join(f"{p:.3f}" for p in X)

        f.write(f"{n} & {chi2:.2f} & $[{params}]$ \\\\\n")

    f.write("\\hline\n")
    f.write("\\end{tabular}\n")
    f.write("\\caption{Fitparameter der genetischen Sinus-Fits}\n")
    f.write("\\end{table}\n")


# Vergleich der chi2 Werte
plt.figure("chi2 Vergleich", figsize=(10, 6))
n_moden_list = [0] + [r['n_moden'] for r in results]
chi2_list = [chi2_lin_result] + [r['chi2'] for r in results]

plt.plot(n_moden_list, chi2_list, 'o-', linewidth=2, markersize=8)
plt.xlabel("Anzahl Sinusmoden")
plt.ylabel("$\chi^2$")
plt.title("Güte des Fits vs. Anzahl der Sinusmoden")
plt.grid(True)
plt.xticks(n_moden_list)
plt.savefig('./Genetische_Algorithmen/plots2/chi2_vergleich.png', dpi=150)


print("\n=== Zusammenfassung ===")
print(f"Linearer Fit: chi2 = {chi2_lin_result:.2f}")
for result in results:
    print(f"{result['n_moden']} Mode(n): chi2 = {result['chi2']:.2f}")
