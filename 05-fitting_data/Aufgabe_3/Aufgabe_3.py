import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import math as m

def polynom(x,*coeff):
    y = 0
    for i, a in enumerate(coeff):
        y += a * x**i
    return y
def legendre_Pn(x,n):
    y = 0
    for i in range(0,m.floor(n/2)+1):
        y += ((-1)**i)*((m.factorial(2*n-2*i))/(m.factorial(n-i) * m.factorial(n-2*i) * m.factorial(i) * 2**n)) * x **(n-2*i)
    return y
def legendre_polynom(x,*coeff):
    y = 0
    i = 0
    for i,a in enumerate(coeff):
        y += a * legendre_Pn(x,i)
    return y
def monom(x,n):
    return x**n
def chi2_polynom(x,y,coeff,sigma,func):
    num = (((y - func(x,*coeff))**2)/sigma**2)
    return np.sum(num) / (np.size(x) - len(coeff))
def matrix_inversion_fit(x,y,sigma,f,deg):
    A = np.zeros((len(x), deg))
    for j in range(deg):
        A[:, j] = f(x,j)
    W = np.diag(1 / sigma**2)
    AWA = A.T @ W @ A
    AWy = A.T @ W @ y
    a = np.linalg.solve(AWA,AWy)
    return a

data = np.array([[-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9],
                [81,50,35,27,26,60,106,189,318,520]])
sigma = np.sqrt(data[1, :])
x_fit = np.linspace(-1,1,100)
deg = 9

# plot
plt.figure("Aufgabe_3_polynom_fit", figsize=(10,8))
plt.plot(data[0,:],data[1,:],'x',label='Messwerte')
for i in range(0,deg):
    popt,pcov = curve_fit(polynom,data[0,:],data[1,:],p0=np.ones(i+1))
    plt.plot(x_fit,polynom(x_fit,*popt),label=fr'Polynom {i}. Ordnung, $\chi^2_{{red.}}$ = {chi2_polynom(data[0,:],data[1,:],popt,sigma,polynom):.2f}')
plt.xlabel(r'$cos(\theta)$')
plt.ylabel("N")
plt.legend()
plt.grid()
plt.title('Polynomiale Anpassung mit curve_fit')
plt.savefig(r"./Aufgabe_3/curve_fit_polynome.png")

plt.figure("Aufgabe3_legendre_fit", figsize=(10,8))
plt.plot(data[0,:],data[1,:],'x',label='Messwerte')
for i in range(1,deg):
    popt,pcov = curve_fit(legendre_polynom,data[0,:],data[1,:],p0=np.ones(i))
    plt.plot(x_fit,legendre_polynom(x_fit,*popt),label=fr'Legendre Polynom {i}. Ordnung, $\chi^2_{{red.}}$ = {chi2_polynom(data[0,:],data[1,:],popt,sigma,legendre_polynom):.2f}')
plt.xlabel(r'$cos(\theta)$')
plt.ylabel("N")
plt.legend()
plt.grid()
plt.title('Legendre Polynom Anpassung mit curve_fit')
plt.savefig(r"./Aufgabe_3/curve_fit_Legendre.png")

plt.figure("Aufgabe3_polynom_fit_inv_matrix", figsize=(10,8))
plt.plot(data[0,:],data[1,:],'x',label='Messwerte')
for i in range(1,deg):
    popt = matrix_inversion_fit(data[0,:],data[1,:],sigma,monom,i)
    plt.plot(x_fit,polynom(x_fit,*popt),label=fr'Polynom {i}. Ordnung, $\chi^2_{{red.}}$ = {chi2_polynom(data[0,:],data[1,:],popt,sigma,polynom):.2f}')
plt.xlabel(r'$cos(\theta)$')
plt.ylabel("N")
plt.legend()
plt.grid()
plt.title('Polynomiale Anpassung durch Matrixinversion')
plt.savefig(r"./Aufgabe_3/polynom_anpassung_matrix.png")

plt.figure("Aufgabe3_legendre_fit_inv_matrix", figsize=(10,8))
plt.plot(data[0,:],data[1,:],'x',label='Messwerte')
for i in range(1,deg):
    popt = matrix_inversion_fit(data[0,:],data[1,:],sigma,legendre_Pn,i)
    plt.plot(x_fit,legendre_polynom(x_fit,*popt),label=fr'Polynom {i}. Ordnung, $\chi^2_{{red.}}$ = {chi2_polynom(data[0,:],data[1,:],popt,sigma,legendre_polynom):.2f}')
plt.xlabel(r'$cos(\theta)$')
plt.ylabel("N")
plt.legend()
plt.grid()
plt.title('Legendre Polynom Anpassung durch Matrixinversion')
plt.savefig(r"./Aufgabe_3/legendre_anpassung_matrix.png")
