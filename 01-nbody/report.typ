#import "@preview/elsearticle:1.0.0": *
#import "@preview/physica:0.9.6": *

#show: elsearticle.with(
  title: "Computational Physics Assignment 1: N-Body Simulation", authors: (
    (
      name: "R. Abele", affiliation: "Eberhard Karls University of Tuebingen",
    ), (name: "N. Matera"),
  ), abstract: "The following exercises showcase several integrators to solve the n-body problem. We were given initial conditions in the form of particle positions and velocities. ", numcol: 1,
)

#outline()

= Background
The following exercises showcase the implementation of several integrators to
simulate the n-body problem. For simplicity, the total mass $M$ as well as the
gravitational constant $G$ are set to 1. The coordinates and velocities of the
particles are normalized so that the simulation is entered and does not drift
over time. We were provided with initial conditions in the form of masses,
positions, and velocities for $n=2, 3, 100, 1000$ 3-dimensional particles.

= The Program
The first part of out program, found under `01-nbody/code/data_normalization` directory,
finds the center of mass and calculates the velocity of the center of mass. This
information is then used to shift all of the positions and velocities of the
particles so that the system does not drift over time.

The main part of the assignment, the actual simulation of planetary movement,
can be found in `01-nbody/code/simulation`. This simulation works by first
calculating the attractive forces between all of the objects and then
determining by how much every particle should be moved in a given time step
considering considering the particle's mass and current velocity. The velocities
of the particles are also updated accordingly and the cycle repeats for the next
time step.

Extrapolation of future particle positions and velocities using the known
information can be performed with varying degrees of accuracy, varying not only
the size of the time step, but also the integrator used.

== Integrators

_Integrators_, as the name suggests integrate the changes in particle position
over time and can be used to predict a future position. There are many kinds of
integrators, but the ones implemented in this assignment are the _Euler, Euler-Cromer, velocity-Verlet, Heun, Hermite, iterated Hermite, Heun,_ and _Runge-Kutta 4_ integrators.

Implementing most of the integrators involves directly following the directions
presented in the manual, but a small calculation involving the jerk and
high-order acceleration derivatives was required to determine the final form of
the Hermite integrator. From the manual, we know that:

$
  1/2 a _(n) ^((2) ) &= -3 (a _(n) - a _(n+1) ^(p) )/(Delta t^2 ) - (2 dot(a) _(n) + dot(a) _(n+1) ^(p) )/(Delta t), \
  1/6 a _(n) ^((3) ) &= 2 (a _(n) - a _(n+1) ^(p) )/(Delta t^3 ) + (dot(a)_(n) + dot(a)_(n+1) ^(p) )/(Delta t^2 ). \
$

Furthermore, we are given that the _corrected_ positions and velocities
calculated by the Hermite integrator can be written as follows:

$
  v _(n+1) ^(c) &= v _(n+1) ^(p) + 1/6 a _(n) ^((2) ) Delta t^3 + 1 / 24 a _(n) ^((3) ) Delta t^4 \
  r _(n+1) ^(c) &= r _(n+1) ^(p) + 1/24 a _(n) ^((2) ) Delta t^4 + 1/120 a _(n) ^( (3) ) Delta t^5 \
$

Some rearranging and substitution results in the following for the corrected
velocity and position:
$
  v _(n+1) ^(c) &= v _(n+1) ^(p) + 1/12 (-6 a _(n) Delta t + 6 a _(n+1) ^(p) Delta t - 5 dot(a)_(n) Delta t^2 - dot(a) _(n+1) ^(p) Delta t^2) \
  r _(n+1) ^(c) &= r _(n+1) ^(p) + 1/60 ( - 9 a _(n) Delta t^2 + 9 a _(n+1 ) ^(p) Delta t^2 - 7 dot(a) _(n) Delta t^3 - 2 dot(a) _(n+1) ^(p) Delta t^3 ). \
$

A modified version of the Hermite integrator, known as the iterated Hermite
integrator can be achieved by first calculating the corrected velocity and using
it to calculated the predicted position, creating a set of equations with the
following form:
$
  v_(n+1) ^(c) &= v_(n) + 1/2 (a_(n+1) ^(p) + a_(n) ) Delta t + 1/12 (dot(a)_(n+1) ^(p) - dot(a)_(n) ) Delta t^2 \
  r_(n+1) ^(c) &= r_(n) + 1/2 (v_(n+1) ^(c) + v_(n) ) Delta t + 1/12 (a_(n+1) ^(p) - a_(n) ) Delta t^2 \
$

= Results
== Two-Body Calculations
The assignment requires us to calculate and plot the following quantities for
the two-body system as a function of time:
$
  log abs((E - E^("start") )/ E^("start")),
  log abs((vb(e) - vb(e) ^("start") ) / vb(e) ^("start")) ,
  log abs((a_(e) - a_(e) ^("start") ) / a_(e) ^("start")), \
$
with $E, vb(e) , "and " a_(e) $ being the energy, Runge-Lenz vector, and
semi-major axis respectively. The plotting of $vb(e) $, however, required a
slight modification of the following form:
$
  log abs((vb(e) - vb(e) ^("start") ) / vb(e) ^("start")) ->
  log abs(vb(e) - vb(e) ^("start")).
$
This modification was made to avoid division by zero when calculating the
Runge-Lenz vector of a circular system (as is the case for the given two-body
system).

After this small explanation for divergence from the given procedure, we proceed
by presenting our findings.

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.01_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a two-body system with a time step
    of 0.01.],
) <2body_0.01_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.05_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a two-body system with a time step
    of 0.05.],
) <2body_0.05_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.1_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a two-body system with a time step
    of 0.1.],
) <2body_0.1_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.5_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a two-body system with a time step
    of 0.5.],
) <2body_0.5_E>

When comparing the relative change energy in the above plots, one can see that
variations in relative energy change are smaller for more accurate integrators,
particularly Runge-Kutta 4, and for smaller time steps.

Simply comparing figures @2body_0.01_E and @2body_0.05_E, one can see that the
scaling of the y-axis already differs by ten orders of magnitude. Looking at the
results for the Euler-Cromer integrator as a specific example, one can see that
the smaller time step of 0.01 results in a reduced peak variation of about 2
orders of magnitude.

In addition to these results, we also see that symplectic integrators,
specifically Euler-Cromer and Velocity-Verlet, do not become less accurate over
time. Even the generally most accurate integrator, Runge-Kutta 4, will show an
increase in the energy change over time, eventually exceeding even the simple
Euler-Cromer integrator. This takes a long time though and results are amplified
for larger time steps, as in figures @2body_0.1_E and @2body_0.5_E.

For a two-body system, it is also considered worthwhile to look at the
eccentricity (or the Runge-Lenz vector) and the size of the semi-major axis of
the system as a measure of simulation accuracy, denoted as *e* and $a_(e) $ here.

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.01_J_comparison.png", width: 90%,
  ), caption: [Plot of Runge-Lenz vector change over time in a two-body system with a time step
    of 0.01.],
) <2body_0.01_J>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.05_J_comparison.png", width: 90%,
  ), caption: [Plot of Runge-Lenz vector change over time in a two-body system with a time step
    of 0.05.],
) <2body_0.05_J>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.1_J_comparison.png", width: 90%,
  ), caption: [Plot of Runge-Lenz vector change over time in a two-body system with a time step
    of 0.1.],
) <2body_0.1_J>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.5_J_comparison.png", width: 90%,
  ), caption: [Plot of Runge-Lenz vector change over time in a two-body system with a time step
    of 0.5.],
) <2body_0.5_J>

Looking at the above plots of the change in Runge-Lenz vector over time for
different time steps, figures @2body_0.01_J, @2body_0.05_J, @2body_0.1_J, and
@2body_0.5_J, we once again see an increase in accuracy with the reduction of
time step size. Interestingly, the symplectic integrators also seem to keep
variation over time constant as well, preventing the slow drift seen in
non-symplectic integrators.

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.01_a_comparison.png", width: 90%,
  ), caption: [Plot of semi-major axis change over time in a two-body system with a time step
    of 0.01.],
) <2body_0.01_a>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.05_a_comparison.png", width: 90%,
  ), caption: [Plot of semi-major axis change over time in a two-body system with a time step
    of 0.05.],
) <2body_0.05_a>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.1_a_comparison.png", width: 90%,
  ), caption: [Plot of semi-major axis change over time in a two-body system with a time step
    of 0.1.],
) <2body_0.1_a>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/2body_0.5_a_comparison.png", width: 90%,
  ), caption: [Plot of semi-major axis change over time in a two-body system with a time step
    of 0.5.],
) <2body_0.5_a>

Looking at the results in figures @2body_0.01_a, @2body_0.05_a, @2body_0.1_a,
and @2body_0.5_a, we see similar results as for the energy and Runge-Lenz vector
over time.

Smaller time steps and more accurate integrators once again generally yield
results with smaller changes in the semi-major axis over time, while the
symplectic integrators maintain the same oscillations over time, avoiding drift.

== N-Body Calculations

For the _N-Body_ part of this assignment, we need only plot the logarithm of the
relative change in energy as a function of time:
$
  log abs((E - E^("start") )/ E^("start")).
$

We begin by looking at the data from a three-body system.

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/3body_0.01_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a three-body system with a time step
    of 0.01.],
) <3body_0.01_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/3body_0.05_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a three-body system with a time step
    of 0.05.],
) <3body_0.05_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/3body_0.1_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a three-body system with a time step
    of 0.1.],
) <3body_0.1_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/3body_0.5_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a three-body system with a time step
    of 0.5.],
) <3body_0.5_E>

Looking at figure @3body_0.01_E, we see that there is once again an oscillating
pattern for relative change in energy for all except the simple Euler
integrator. Looking at the plots with a greater time step, figures
@3body_0.05_E, @3body_0.1_E, and @3body_0.5_E, we see the performance
differences of the integrators more clearly and the slow increase in error of
all except the symplectic integrators.

We now continue with analysis of the one hundred-body system.

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/100body_0.01_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a one hundred-body system with a
    time step of 0.01.],
) <100body_0.01_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/100body_0.05_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a one hundred-body system with a
    time step of 0.05.],
) <100body_0.05_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/100body_0.1_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a one hundred-body system with a
    time step of 0.1.],
) <100body_0.1_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/100body_0.5_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a one hundred-body system with a
    time step of 0.5.],
) <100body_0.5_E>

As can be seen in the plots of the one hundred-body system above for varying
time steps (see figures @100body_0.01_E, @100body_0.05_E, @100body_0.1_E,
@100body_0.5_E), energy is not predictably conserved in the one hundred-body
system. Accuracy in energy generally falls with time, as expected, but it seems
to often increase in 'explosive' leaps, as seen most clearly in figure
@100body_0.01_E. These sudden increases in the relative energy hint at a limit
with such simple n-body simulations - when masses are very close together, the
force that they exert on each other increases in proportion to $1/r$. The can
occasionally produce unrealistic results since the collision of planets is not
accounted for and they can move extremely close to each other.

Another surprising result seen in the data for the one hundred-body simulation
is that the precision of the various integrators does not seem to follow the
expected pattern of Euler being the worst and RK4 being the best. We are not
sure if this is an implementation error or a fact of the complexity presented in
a one hundred-body simulation. It should be noted that the symplectic operators
Euler-Cromer and Velocity-Verlet once again seem to do a decent job preserving
energy over time, though even this does not follow this nice cyclic patterns
observed in the two and three-body cases.

Similar results follow for the data of the one thousand-body simulation.

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/1kbody_0.01_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a one thousand-body system with a
    time step of 0.01.],
) <1kbody_0.01_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/1kbody_0.05_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a one thousand-body system with a
    time step of 0.05.],
) <1kbody_0.05_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/1kbody_0.1_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a one thousand-body system with a
    time step of 0.1.],
) <1kbody_0.1_E>

#figure(
  image(
    "./code/simulation/sim_data/data_calc/plots/1kbody_0.5_E_comparison.png", width: 90%,
  ), caption: [Plot of relative energy change over time in a one thousand-body system with a
    time step of 0.5.],
) <1kbody_0.5_E>

Looking at the above figures @1kbody_0.01_E, @1kbody_0.05_E, @1kbody_0.1_E, and
@1kbody_0.5_E for the relative energy change of the one thousand-body system
over time, we once again see sudden increases in energy difference and no clear
pattern of which integrator is more accurate.

In the description of the assignment, we are also asked to discuss observed
increase in computation required for running the simulations with an increasing
number of particles $N$. Though we did not take exact measurements, the results
seemed to follow the expected $N^2 $ proportionality for calculation time, with
the one thousand-body system taking about one hundred times longer than the one
hundred-body system (corresponding directly to the ten-fold increase in
particles).

= Summary

All in all, the results of the simulation generally followed expected trends.
Symplectic integrators generally minimized energy drift over time, though this
pattern did not seem to be very consistent for the largest systems. The simplest
integrator, the Euler integrator usually performed the worst, while the most
widespread integrator, the Runge-Kutta 4 integrator, performed the best.

Most of the results followed expected trends, though the one hundred and one
thousand-body simualtions seemed to show some irregularities, likely caused by
particles getting too close to each other and exerting non-realistic forces.

In conclusion, this lab demonstrated the usefulness of various integrators and
some of the shortcomings that they may come with.
