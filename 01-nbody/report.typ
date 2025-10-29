#import "@preview/elsearticle:1.0.0": *
#import "@preview/physica:0.9.6": *

#show: elsearticle.with(
  title: "Computational Physics Assignment 1: N-Body Simulation", authors: (
    (
      name: "R. Abele", affiliation: "Eberhard Karls University of Tuebingen",
    ), (name: "N. Matera"),
  ), abstract: "The following exercises showcase several integrators to solve the n-body problem. We were given initial conditions in the form of particle positions and velocities. ",
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
finds the center of mass and calcualtes the velocity of the center of mass. This
information is then used to shift all of the positions and velocities of the
particles so that the system does not drift over time.

The main part of the assignment, the actual simulation of planetary movement,
can be found in `01-nbody/code/simulation`. This simulation works by first
calculating the attractive forces between all of the objects and then
determining by how much every particle should be moved in a given timestep
considering considering the particle's mass and current velocity. The velocities
of the particles are also updated accordingly and the cycle repeats for the next
time step. the particle's mass and current velocity.

Extrapolation of future particle positions and velocities using the known
infomation can be performed with varrying degrees of accuracy, varrying not only
the size of the timestep, but also the integrator used.

_Integrators_, as the name suggests integrate the changes in particle position
over time and can be used to predict a future position. There are many kinds of
integrators, but the ones implemented in this assignment are the _Euler, Euler-Cromer, velocity-Verlet, Heun, Hermite, iterated Hermite, Heun,_ and _Runge-Kutta 4_ integrators.

Implementing most of the integrators involved following the directions presented
in the manual, but a small calculation involving the jerk and high-order
acceleration derivatives was required to determine the final form of the Hermite
integrator. From the manual, we know that:

$
  1/2 a _(n) ^((2) ) &= -3 (a _(n) - a _(n+1) ^(p) )/(Delta t^2 ) - (2 dot(a) _(n) + dot(a) _(n+1) ^(p) )/(Delta t), \
  1/6 a _(n) ^((3) ) &= 2 (a _(n) - a _(n+1) ^(p) )/(Delta t^3 ) + (dot(a)_(n) + dot(a)_(n+1) ^(p) )/(Delta t^2 ). \
$

From which it follows:
$
  a _(n) ^((2) ) &= -6 (a _(n) - a _(n+1) ^(p) )/(Delta t^2 ) - 2(2 dot(a) _(n) + dot(a) _(n+1) ^(p) )/(Delta t), \
  a _(n) ^((3) ) &= 12 (a _(n) - a _(n+1) ^(p) )/(Delta t^3 ) + 6(dot(a)_(n) + dot(a)_(n+1) ^(p) )/(Delta t^2 ). \
$

We are given that the _corrected_ positions and velocities calculated by the
Hermite integrator can be written as follows:
