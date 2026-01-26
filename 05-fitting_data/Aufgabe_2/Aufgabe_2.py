import numpy as np
import matplotlib.pyplot as plt

def I(U,a,b):
    return a*U + b # a = 1/R, b = I_0
def chi2(x,y,a,b,sigma):
    num = ((y - a - b*x)/sigma)**2
    return np.sum(num)
def linear_fit(x,y,y_err,I0):
    S = np.sum(1/y_err**2)
    S_x = np.sum(x/y_err**2)
    S_y = np.sum(y/y_err**2)
    S_xx = np.sum(x**2/y_err**2)
    S_xy = np.sum(x*y/y_err**2)
    D = S*S_xx - S_x**2
    if I0:
        a = (S_xx*S_y - S_x*S_xy)/(D)
        b = (S*S_xy - S_x*S_y)/(D)
        sigma_a = np.sqrt(S_xx/D)
        sigma_b = np.sqrt(S/D)
        chi = chi2(x,y,a,b,y_err)
        chi2_red = chi/(x.size-2)
        return a,b,sigma_a,sigma_b,chi2_red
    else:
        b = S_xy/S_xx
        sigma_b = np.sqrt(S_x/S_xx)
        a=0
        chi2_red = chi2(x,y,0,b,y_err)/(x.size-1)
        return b,sigma_b,chi2_red


data = np.array([[0.5,1.0,1.5,2.0,2.5,3.0,3.5,4.0,4.5,5.0,5.5,6.0],
                 [0.065,0.206,0.405,0.492,0.606,0.782,0.865,1.018,1.199,1.327,1.408,1.627],
                 [0.01,0.01,0.02,0.02,0.02,0.02,0.02,0.03,0.03,0.03,0.03,0.04]])

a,b,sigma_a,sigma_b,chi2_red = linear_fit(data[0,:],data[1,:],data[2,:],True)
c,sigma_c,chi2_red_c = linear_fit(data[0,:],data[1,:],data[2,:],False)

with open(r"./Aufgabe_2/ergebnisse_2.txt", "w") as file:
    file.write(f'I_0: {a} +- {sigma_a}\n')
    file.write(f'R: {1/b} +- {sigma_b/b**2}\n')
    file.write(f'chi2_red: {chi2_red}\n')
    file.write(f'R_no_I0: {1/c} +- {sigma_c/c**2}\n')
    file.write(f'chi2_red: {chi2_red_c}\n')
    file.close()
# Print
print(f'I_0: {a} +- {sigma_a}')
print(f'R: {b} +- {sigma_b/b**2}')
print(f'chi2_red: {chi2_red}')
print(f'R_no_I0: {1/c} +- {sigma_c/c**2}')
print(f'chi2_red: {chi2_red_c}')
U_fit = np.linspace(0.5,6,100)
fit = I(U_fit,b,a)
I0_fit = I(U_fit,c,0)
# Plot
plt.figure('Aufgabe 2', figsize=(10,8))
plt.errorbar(data[0,:],data[1,:],yerr = data[2,:],label='Messwerte',fmt='x',capsize=5)
plt.plot(U_fit,fit,label=r'Fit mit $I_0$')
plt.plot(U_fit,I0_fit,label=r'Fit ohne $I_0$')
plt.legend()
plt.xlabel('U [V]')
plt.ylabel('I [A]')
plt.title(r'Stromstärke Messdaten vs Fit mit $I_0$ vs Fit ohne $I_0$')
plt.grid()
plt.savefig(r"./Aufgabe_2/ergebnisse_2.png")