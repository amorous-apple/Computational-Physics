#import "@preview/elsearticle:1.0.0": *
#import "@preview/physica:0.9.6": *

#show: elsearticle.with(
  title: "Computational Physics Assignment 1: N-Body Simulation", authors: (
    (
      name: "R. Abele", affiliation: "Eberhard Karls University of Tuebingen",
    ), (name: "N. Matera"),
  ), abstract: "The following exercises showcase several integrators to solve the n-body problem. We were given initial conditions in the form of particle positions and velocities. ", numcol: 1,
)

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

= Evaluation
== Two-Body Calculations
== N-Body Calculations
