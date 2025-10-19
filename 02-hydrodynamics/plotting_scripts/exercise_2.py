#!/usr/bin/env python
# Import the Riemann solver library. Note that this will only work if the file
# 'riemannsolver.py' is in the same directory as this script.
import riemannsolver
# Import the Python numerical libraries, as we need them for arange.
import numpy as np
# Import Matplotlib, which we will use to plot the results.
import matplotlib.pyplot as plt

################################################################################
# some global definitions
################################################################################

# the constant adiabatic index
GAMMA = 1.4

# the Riemann solver
solver = riemannsolver.RiemannSolver(GAMMA)

# the constant time step
timestep = 0.001

# number of steps
numstep = 228

# number of cells
numcell = 100

################################################################################
# the actual program
################################################################################

# numerical data

rho = np.loadtxt(r"./output2/rho.txt", delimiter= ";")
u = np.loadtxt(r"./output2/u.txt", delimiter= ";")
p = np.loadtxt(r"./output2/p.txt", delimiter= ";")
epsilon = np.loadtxt(r"./output2/epsilon.txt", delimiter= ";")
T = np.loadtxt(r"./output2/T.txt", delimiter= ";")
xb = np.loadtxt(r"./output2/xb.txt", delimiter= ";")


# reference solution: as the Sod shock problem is in fact a Riemann problem,
# this is just the actual solution of the Riemann problem, evaluated at the
# final time of the simulation.
xref = np.arange(-0.5, 0.5, 0.001)
rhoref = np.array([solver.solve(1., 0., 1., 0.125, 0., 0.1, x / (timestep * numstep))[0] for x in xref])
uref   = np.array([solver.solve(1., 0., 1., 0.125, 0., 0.1, x / (timestep * numstep))[1] for x in xref])
pref   = np.array([solver.solve(1., 0., 1., 0.125, 0., 0.1, x / (timestep * numstep))[2] for x in xref])

eref = pref / ((GAMMA - 1.0) * rhoref)
Tref = (GAMMA - 1.0) * eref
xref = xref + 0.5

fig, ax = plt.subplots(4)
fig.figsize=(15,8)
fig.tight_layout(h_pad=2)
fig.subplots_adjust(top=0.9,left = 0.1, right = 0.9, bottom = 0.1)

# plot the reference solution and the actual solution
ax[0].plot(xref, rhoref, c='b', lw=2, label='analytical solution')
ax[0].plot(xb[2:102], rho[2:102], label='numerical solution', color = 'orange', ls = '--')   
ax[1].plot(xref, uref, lw=2, c='r', label='$t=0.2$')
ax[1].plot(xb[2:102], u[2:102], label='numerical solution',c = 'orange', ls = '--')
ax[2].plot(xref, pref, lw=2, c='orange', label='$t=0.2$')
ax[2].plot(xb[2:102], p[2:102], label='numerical solution',c = 'orange', ls = '--')
ax[3].plot(xref, Tref, label='analytical solution',c = 'blue')
ax[3].plot(xb[2:102], T[2:102], label='numerical solution',c = 'orange', ls = '--')
ax[0].legend(fontsize=6)

ax[0].set_title("Shock Tube Problem, t=0.228s")
#pl.plot([cell._midpoint for cell in cells], [cell._density for cell in cells], "k.")


ax[3].set_xlabel(r'$x$')
# ax[0].set_ylim(-0.01,1.1)
# ax[2].set_ylim(-0.01,)
# ax[1].set_ylim(-0.01,0.8)
ax[0].set_ylabel("density")
ax[1].set_ylabel("velocity")
ax[2].set_ylabel("pressure")
ax[3].set_ylabel("temperature")
# save the plot as a PNG image
fig.savefig("sodshock_analytical.pdf")
plt.savefig(f"./plots2/shocktube.png")
