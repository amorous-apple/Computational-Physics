from geneticalgorithm import geneticalgorithm as ga
import numpy as np
import matplotlib.pyplot as plt

n = 9 
sigma2 = 0.15

# Aufgabe 1a: Konzentrische Wellen
def f_1(X):
    x, y = X
    r2 = (x-0.5)**2 + (y-0.5)**2
    return -np.cos(n*np.pi*np.sqrt(r2))**2 * np.exp(-r2/sigma2)

# Aufgabe 1b: Zwei 2D-Gaußverteilungen
def f_2(X):
    x, y = X
    r_12 = (x-0.5)**2 + (y-0.5)**2
    r_22 = (x-0.6)**2 + (y-0.1)**2
    return -0.8 * np.exp(-r_12/(0.3)**2) + 0.879008 * np.exp(-r_22/(0.03)**2)

# Parameter für beide Probleme
varbound = np.array([[0, 1], [0, 1]])

algorithm_param = {
    'max_num_iteration': 1000,
    'population_size': 100,
    'mutation_probability': 0.1,
    'elit_ratio': 0.01,
    'crossover_probability': 0.5,
    'parents_portion': 0.3,
    'crossover_type': 'uniform',
    'max_iteration_without_improv': None
}

# Aufgabe 1a ausführen
model_1 = ga(function=f_1, dimension=2, variable_type='real', 
             variable_boundaries=varbound, 
             algorithm_parameters=algorithm_param, 
             convergence_curve=True)
model_1.run()

print("Aufgabe 1a - Maximum von f_1:")
print(f"Position: x={model_1.output_dict['variable'][0]:.6f}, y={model_1.output_dict['variable'][1]:.6f}")
print(f"Funktionswert (Maximum): {-model_1.output_dict['function']:.6f}")

# Aufgabe 1b ausführen
model_2 = ga(function=f_2, dimension=2, variable_type='real', 
             variable_boundaries=varbound, 
             algorithm_parameters=algorithm_param, 
             convergence_curve=True)
model_2.run()

print("\nAufgabe 1b - Maximum von f_2:")
print(f"Position: x={model_2.output_dict['variable'][0]:.6f}, y={model_2.output_dict['variable'][1]:.6f}")
print(f"Funktionswert (Maximum): {-model_2.output_dict['function']:.6f}")

plt.figure("GA Konvergenz", figsize=(12, 5))

plt.subplot(1, 2, 1)
if len(model_1.report) > 0:
    convergence_1 = -1 * np.array(model_1.report)
    plt.plot(convergence_1)
else:
    print("model_1.report ist leer")

plt.xlabel('Iteration')
plt.ylabel('Funktionswert (Maximum)')
plt.title(r'Aufgabe 1a: Konvergenz von $f_1$')
plt.grid(True)

plt.subplot(1, 2, 2)
if len(model_2.report) > 0:
    convergence_2 = -1 * np.array(model_2.report)
    plt.plot(convergence_2)
    
else:
    print("model_2.report ist leer")

plt.xlabel('Iteration')
plt.ylabel('Funktionswert (Maximum)')
plt.title(r'Aufgabe 1b: Konvergenz von $f_2$')
plt.grid(True)

plt.tight_layout()
plt.savefig('./Genetische_Algorithmen/plot1.png')
