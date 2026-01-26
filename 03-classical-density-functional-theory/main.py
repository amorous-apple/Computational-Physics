import numpy as np
import matplotlib.pyplot as plt
from numba import jit
import os

# --- Analytical Functions ---

@jit(nopython=True)
def phi_0D(eta):
    return eta + (1 - eta) * np.log(1 - eta)

@jit(nopython=True)
def phi_0D_prime(eta):
    return -np.log(1 - eta)

def analytical_mu_ex(rho0, L, beta=1.0):
    mu_ex_derived = (1/beta) * ( L * phi_0D_prime(L*rho0) - (L-1)*phi_0D_prime((L-1)*rho0) )
    return mu_ex_derived

def analytical_pressure(rho0, L, beta=1.0):
    n1 = L * rho0
    n0 = (L - 1) * rho0
    
    return (1 / beta) * np.log((1 - n0) / (1 - n1))

def analytical_gamma(rho0, L, beta=1.0):
    """
    Analytical surface tension from Eq. (2.22)
    """
    mu_ex = analytical_mu_ex(rho0, L, beta)
    p = analytical_pressure(rho0, L, beta)
    gamma = 0.5 * (mu_ex - (2 * L - 1) * p)
    return gamma

# --- Core DFT Functions ---

@jit(nopython=True)
def calculate_weighted_densities(rho, L):
    M = len(rho)
    n1 = np.zeros(M)
    n0 = np.zeros(M)
    for s in range(L - 1, M):
        n1[s] = np.sum(rho[s - L + 1 : s + 1])
        n0[s] = np.sum(rho[s - L + 1 : s])
    return n1, n0

@jit(nopython=True)
def calculate_mu_s_ex(rho, L):
    M = len(rho)
    mu_ex_s = np.zeros(M)
    n1, n0 = calculate_weighted_densities(rho, L)

    phi_prime_n1 = np.zeros_like(n1)
    phi_prime_n0 = np.zeros_like(n0)
    for i in range(len(n1)):
        phi_prime_n1[i] = phi_0D_prime(n1[i])
        phi_prime_n0[i] = phi_0D_prime(n0[i])

    for s in range(M):
        sum1 = 0.0
        sum2 = 0.0
        # Summation for the first term
        for s_prime in range(s, min(s + L, M)):
            sum1 += phi_prime_n1[s_prime]
        # Summation for the second term
        for s_prime in range(s + 1, min(s + L, M)):
            sum2 += phi_prime_n0[s_prime]
        mu_ex_s[s] = sum1 - sum2 # beta is 1
    return mu_ex_s

@jit(nopython=True)
def run_picard_iteration(rho_initial, mu, L, alpha, max_steps, tol):
    """
    Solves for the equilibrium density profile using Picard iteration
    """
    rho = np.copy(rho_initial)
    M = len(rho)

    # External potential for hard walls
    V_ext = np.zeros(M)
    V_ext[:L] = np.inf
    V_ext[M-L:] = np.inf

    exp_neg_beta_Vext = np.exp(-1.0 * V_ext)

    for i in range(max_steps):
        mu_ex_s = calculate_mu_s_ex(rho, L)
        rho_new_arg = mu - mu_ex_s
        rho_new_arg = np.minimum(rho_new_arg, 100.0) 
        rho_new = np.exp(rho_new_arg) * exp_neg_beta_Vext
        rho_next = (1 - alpha) * rho + alpha * rho_new
        error = np.sum((rho_new - rho)**2)
        if error < tol:
            return rho_next
        rho = rho_next
    return rho

# --- Post-processing Functions ---

def calculate_numerical_gamma(rho_eq, rho0, L, beta=1.0):
    """
    Calculates the numerical surface tension from the excess grand potential.
    """
    M = len(rho_eq)
    fluid_domain_size = M - 2*L
    mu = mu_from_rho0(rho0, L, beta)
    p_bulk = analytical_pressure(rho0, L, beta)

    # Ideal gas part F_id
    with np.errstate(divide='ignore', invalid='ignore'):
        f_id_density = (1/beta) * rho_eq * (np.log(rho_eq) - 1)
        f_id_density[np.isnan(f_id_density)] = 0
    F_id = np.sum(f_id_density)

    # Excess part F_ex
    n1, n0 = calculate_weighted_densities(rho_eq, L)
    phi_n1 = np.array([phi_0D(eta) for eta in n1])
    phi_n0 = np.array([phi_0D(eta) for eta in n0])
    F_ex = (1/beta) * np.sum(phi_n1 - phi_n0)

    # Omega = F - mu * N
    N_total = np.sum(rho_eq)
    Omega_inhom = F_id + F_ex - mu * N_total
    Omega_bulk = -p_bulk * fluid_domain_size
    gamma = 0.5 * (Omega_inhom - Omega_bulk)

    return gamma

def calculate_adsorption(rho_eq, rho0, L):
    """
    Calculates the excess adsorption Gamma
    """
    M = len(rho_eq)
    s_start_idx = L
    s_end_idx = M - L 
    adsorption_sum = np.sum(rho_eq[s_start_idx:s_end_idx] - rho0)
    return 0.5 * adsorption_sum

def mu_from_rho0(rho0, L, beta=1.0):
    """
    Calculates the full chemical potential mu for a given bulk density rho0.
    """
    if rho0 <= 1e-12: return -np.inf
    mu_id = (1/beta) * np.log(rho0) 
    mu_ex = analytical_mu_ex(rho0, L, beta)
    return mu_id + mu_ex

# --- Main Simulation ---

# --- Simulation Parameters ---
M = 1000                # Number of grid points
alpha = 0.001           # Mixing parameter
max_steps = 100000      # Max iterations
tol = 1e-9              # Convergence tolerance
beta = 1.0              # Inverse temperature (set to 1)           

L_values = [3, 10]
eta0_values = np.arange(0.1, 0.91, 0.1)

results = {}

for L in L_values:
    print(f"\n--- Running for L = {L} ---")
    results[L] = { 
        'eta0': [], 'mu': [], 
        'gamma_ana': [], 'gamma_num': [], 
        'adsorption_eq': [], 'adsorption_grad': [], 
        'profiles': [] 
    }
    
    for eta0 in eta0_values:
        rho0 = eta0 / L
        mu = mu_from_rho0(rho0, L, beta)
        if np.isinf(mu):
            print(f"Skipping eta0 = {eta0:.1f} (density too high).")
            continue

        rho_initial = np.full(M, rho0)
        rho_initial[:L] = 0
        rho_initial[M-L:] = 0
        
        rho_eq = run_picard_iteration(rho_initial, mu, L, alpha, max_steps, tol)
        
        gamma_ana = analytical_gamma(rho0, L)
        gamma_num = calculate_numerical_gamma(rho_eq, rho0, L, beta)
        adsorption_eq = calculate_adsorption(rho_eq, rho0, L)
        
        # Calculating gamma using mu + dmu and mu - dmu
        d_eta = 1e-5
        
        # right point
        eta_p = eta0 + d_eta
        if eta_p < 1.0:
            rho_p = eta_p / L
            mu_p = mu_from_rho0(rho_p, L, beta)
            gamma_p = analytical_gamma(rho_p, L, beta)
        else:
            mu_p = mu
            gamma_p = gamma_ana

        # left point
        eta_m = eta0 - d_eta
        rho_m = eta_m / L
        mu_m = mu_from_rho0(rho_m, L, beta)
        gamma_m = analytical_gamma(rho_m, L, beta)
        
        d_gamma = gamma_p - gamma_m
        d_mu_val = mu_p - mu_m
        
        adsorption_grad_local = - d_gamma / d_mu_val
        
        print(f"eta0={eta0:.1f} | y_ana={gamma_ana:.4e} | y_num={gamma_num:.4e} | Gamma_eq={adsorption_eq:.4e} | Gamma_grad={adsorption_grad_local:.4e}")

        results[L]['eta0'].append(eta0)
        results[L]['mu'].append(mu)
        results[L]['gamma_ana'].append(gamma_ana)
        results[L]['gamma_num'].append(gamma_num)
        results[L]['adsorption_eq'].append(adsorption_eq)
        results[L]['adsorption_grad'].append(adsorption_grad_local) 
        results[L]['profiles'].append(rho_eq)

# --- Plotting ---

# Plot Density Profiles (Task 4)
fig1, axes1 = plt.subplots(1, 2, figsize=(14, 6))
for i, L in enumerate(L_values):
    ax = axes1[i]
    for j, eta0 in enumerate(results[L]['eta0']):
        profile = results[L]['profiles'][j]
        
        plot_start_idx = L - 1
        
        plot_range = min(plot_start_idx + 10 * L, M // 2) 
        
        s_axis = np.arange(len(profile)) - L + 1
        ax.plot(s_axis[plot_start_idx:plot_range], profile[plot_start_idx:plot_range], label=fr"$\eta_0$={eta0:.1f}")
    
    ax.set_title(f"L = {L}", fontsize=18)
    ax.set_xlabel("s (Position, boundary at s=0)", fontsize=18)
    ax.set_ylabel(r"$\rho(s)$", fontsize=18)
    ax.legend()
    ax.grid(True, linestyle='--', alpha=0.6)
    ax.set_xlim(left=0)

fig1.suptitle("Density Profile at the boundary", fontsize=22)
plt.tight_layout()
plt.savefig(f"./plots/1.png")
plt.close()

# Plot Gibbs Adsorption Check (Task 6)
fig2, axes2 = plt.subplots(1, 2, figsize=(14, 6))
for i, L in enumerate(L_values):
    ax = axes2[i]

    valid_indices = ~np.isinf(results[L]['gamma_ana'])
    valid_eta0 = np.array(results[L]['eta0'])[valid_indices]
    valid_adsorption_eq = np.array(results[L]['adsorption_eq'])[valid_indices]
    valid_adsorption_grad = np.array(results[L]['adsorption_grad'])[valid_indices]

    ax.plot(valid_eta0, valid_adsorption_eq, 'o-', label="using equation (2.23)")
    ax.plot(valid_eta0, valid_adsorption_grad, 's-', label="using gradient (-dγ/dμ)")
    ax.set_title(f"L = {L}")
    ax.set_xlabel(r"$\eta_0$")
    ax.set_ylabel(r"$\Gamma$ (Adsorption)")
    ax.legend()
    ax.grid(True, linestyle='--', alpha=0.6)

fig2.suptitle("Verification of Gibbs' Adsorption Equation (Task 6)")
plt.tight_layout()
plt.savefig(f"./plots/2.png")
plt.close()


# Print numerical vs analytical gamma table (Task 5)
print("\n--- Numerical vs. Analytical Surface Tension (Task 5) ---")
print(f"{'L':<4} {'eta0':<6} {'gamma_num':<15} {'gamma_ana':<15} {'Difference':<15}")
print("-" * 55)
for L in L_values:
    for i, eta0 in enumerate(results[L]['eta0']):
        g_num = results[L]['gamma_num'][i]
        g_ana = results[L]['gamma_ana'][i]
        diff = g_num - g_ana
        print(f"{L:<4} {eta0:<6.1f} {g_num:<15.4e} {g_ana:<15.4e} {diff:<15.4e}")

