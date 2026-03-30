#import "@preview/elsearticle:1.0.0": *
#import "@preview/physica:0.9.6": *

#show: elsearticle.with(
  title: "Computational Physics Assignment 4: Ising Model",
  authors: (
    (
      name: "R. Abele",
      affiliation: "Eberhard Karls University of Tuebingen",
    ),
    (name: "N. Matera"),
  ),
  abstract: "The following exercises showcase several uses of Monte Carlo methods, specifically highlighting their use in simulating the Ising model.",
  numcol: 1,
)

#outline()

= Background

= Program

The programs for this series of problems were written using Rust. A `nix flake` is used to manage the programming environment and necessary dependencies; the programming environment can be entered by running `nix develop` (assuming that `nix` is installed). From there, one can run `cargo run` in any directory containing a Rust project to compile and run the program.

Results can be plotted by running `python3 ./<plotting_script_name>` in the directory containing the corresponding python script.

Note: All programs should be run in release mode with `cargo run --release` for optimal performance!
= Tasks
== Task 1
=== Part A
The first part of task 1 asks us to calculate $pi$ numerically through a Monte Carlo simulation involving the random distribution of points $(x,y)$ in the unit square.

The area of a circle is of course
$
  a & = pi r^2 \
$
and that of the unit square is 1. If we center a circle with radius $r = 1$ on the origin, then the fraction of the unit square covered by the circle $f$ is given by
$
       f & = (pi r^2) / 4 \
         & = pi / 4 \
  ==> pi & = 4 f. \
$
Furthermore, we can easily determine if a point $(x,y,)$ is in a unit circle by checking if its radius $r$ is less than 1.
$
      x^2 + y^2 & < r^2 \
  ==> x^2 + y^2 & < 1 \
$

Ergo, we can create a program for this task by generating $q$ random points $(x,y)$ with $x,y in [0 , 1)$, and calculate the number of points within the unit circle $p$, meaning that
$
  pi & = 4f = (4 p) /q. \
$
To show convergence for this task with consistent results, a seed-based random number generator is used and the logarithm of the error is plotted as a function of the $log_(10)$ points used.

#figure(
  image("./code/problem1/part_a/convergence_plot.png"),
  caption: "Plot of the error of the Pi Approximation as a function of Points used",
) <pi_approximation>

As seen in @pi_approximation, there is a steady decrease in the natural log of the error as a function of $log_10 ("iterations")$, indicating the expected increase in precision following an increase in data points.




=== Part B
This task asks us to first create a random number generator following a Gaussian distribution with an average $mu$ and a width $sigma$. This function should then be used to calculate the following integral through MC Integration:
$
  I & = (2 pi)^(-2) integral_(-infinity)^(infinity)"d"t" "cos (t) exp (-t^2 /2). \
$
We are given the analytical value $I = e^(-1/2) approx 0.606531$ to check our answer.

When checked through numerical and analytical integration methods though, it is found that the value of the integral in the above expression is as follows:
$
  integral_(infinity)^(-infinity)"d"t" "cos (t) e^(- t^2 /2) &= sqrt(2 pi) / sqrt(e). \
$
This of course would not cancel out with the term $(2 pi)^(-2)$, leading us to conclude that the constant in front contains a mistake and should instead be $(2 pi)^(-1/2)$. When this change is implemented, the integral $I &= e^(-1/2)$ as desired.

We know that the standard normal distribution $f (x)$ is given by
$
  f (x) & = (1)/(sqrt(2 pi sigma^2) ) e^(- (x - mu)^2 / 2 sigma^2 ). \
$

In our case $mu = 0$ and $sigma = 1$, yielding
$
  f (x) & = 1 / sqrt(2 pi) e^(- x^2 / 2). \
$

Knowing this, we can refactor our given integral as follows:
$
  I & = 1 / (2pi)^(1/2) integral_(infinity)^(-infinity)"d"t" "cos (t) e^(- t^2 /2) \
  &= sqrt(2 pi) / sqrt(2 pi) integral_(infinity)^(-infinity)"d"t" "cos (t) [1 / sqrt(2 pi) e^(- t^2 / 2) ] \
  &= integral_(infinity)^(-infinity)"d"t" "cos (t) f (t). \
$

$f (x)$ is of course normalized, meaning that
$
  integral_(infinity)^(-infinity)"d"x" "f (x) = 1. \
$

This in turn means that we replace $f (t)$ in the integral by selecting points according to this normal distribution:
$
  I & = 1 / N sum_(i = 0)^(N) cos (x_(i) ) \
$
with $N$ being the number of data points used and $x$ being a normally distributed random value.


The required normal distribution is realized by using two uniformly generated numbers and a Box-Muller transform. The two random numbers $x,y in (0, 1 ]$ are processed as follows:
$
      R & = sqrt(- 2 dot ln x) \
  theta & = 2 pi y, \
$
which can then be used to calculate the two normally distributed values $Z_(0) ,Z_(1)$
$
  Z_(0) & = R cos (theta) \
  Z_(1) & = R sin (theta). \
$

We account for the modification of $sigma$ and $mu$ by adding them as follows:
$
      R & = sigma dot sqrt(-2 ln x), \
  theta & = 2 pi y,
$

$
  Z_0 & = R cos (theta) + mu, \
  Z_1 & = R sin ( theta) + mu. \
$

Like in `part A`, a seed-based random number generator is used and the logarithm of the error is plotted as a function of the $log_(10)$ points used.

#figure(
  image("./code/problem1/part_b/convergence_plot.png"),
  caption: "Plot of the error of the integral approximation as a function of points used",
) <integral_approximation>

Like in figure @pi_approximation, figure @integral_approximation shows a steady decrease in the error as the number of points used is increased, confirming the methodology of the method used.

== Task 2
In `Task 2` we are asked to simulate the Ising-Model in $d = 2$ dimensions with a disappearing external field $h = 0$ and periodic boundary conditions on an $L times L$ grid.
We are tasked with determining the energy density $epsilon = expval(H)/ L^2$, $expval(m)$, as well as $expval(abs(m))$ as a function of the inverse temperature $beta in [0 , 1]$ through direct summation over all possible configurations. We are asked to use grid sizes $L = 2 , 3, 4$. Finally, we compare the numerical results obtained to the analytical ones found in the lab manual.

=== Theory

A general expectation value $expval(G)$ is described by the equation
$
  expval(G) & = sum_(omega in Omega)^() G (omega) P_(beta) (omega), \
$
with $omega$ describing one possible spin-configuration in the set of all possible configurations $Omega$ and $P_(beta) (omega)$ corresponding to the Boltzman probability from the manual:
$
  P_(beta) (omega) & = Z^(-1) e^( -beta H (omega) ), \
  Z & eq.triple sum_(omega in Omega)^() e^(-beta H (omega) ) = "tr" e^(-beta H). \
$
Here $beta$  refers to the inverse temperature $beta = 1 / k_(b) T$.

Using this equation, we now calculate $expval(H)$ as follows:
$
  expval(H) & = sum_(omega in Omega)H (omega) P_(beta) (omega) \
$
with $H$ given in the lab manual as
$
  H & = - J sum_(expval(x"," y))^() s_(x) s_(y) - h sum_(x in Lambda)^()s_(x), \
$

where $expval(x"," y)$ denoting the sum over all $s_(x)$ and its $2d$ nearest neighbors $s_(y)$.
For the purpose of our simulation, we set $J = 1$ and $h = 0$, resulting in the simplified expression.

$
  H & = - sum_(expval(x"," y))^() s_(x) s_(y). \
$

In short, we now have
$
  expval(H) & = sum_(omega in Omega)^() H (omega) Z^(-1) e^(-beta H (omega) ) \
            & = Z^(-1) sum_(omega in Omega)^() H e^(-beta H) \
            & = (sum_(omega in Omega)^() H e^(-beta H)) /
              (sum_(omega in Omega)^() e^(-beta H)) \
            & eq.triple E_("sum") / Z. \
$
The reason for this refactoring is that we can now calculate both $E_("sum")$ and $Z$ in a single loop through $omega in Omega$ and divide in the end to obtain $expval(H)$. This saves us from having to run the loop once to calculate $Z$ and then once to calculate the weighted sum.

Once we know $expval(H)$, calculating the energy density $epsilon$ for a grid of size $L$ is trivial:
$
  epsilon & = expval(H)/ L^2. \
$

Proceeding with the calculation of the expected magnetization $expval(m)$, we first calculate the magnetization of a single state
$
  m & = 1/ L^2 sum_(x in Lambda)^() s_(x), \
$
where $s_(x) in {-1,1 }$ is a single spin at the coordinate $x$  on the $L times L$ crystal lattice $Lambda$.

Following the same procedure as above, $expval(m)$ is given by
$
  expval(m) & = Z^(-1) sum_(omega in Omega)^() m (omega) e^(-beta H (omega) ). \
$
$expval(abs(m))$ is then given by
$
  expval(abs(m)) & = Z^(-1) sum_(omega in Omega)^() abs(m (omega)) e^(-beta H (omega) ). \
$

With all of the desired values having the same bounds of summation over all possible states $Omega$ , the values at a given inverse temperature $beta$ can be calculated with a single loop iteration.

In the lab manual we are given the following analytical solution for the energy density:
$
  epsilon (beta) &= -J coth(2 beta J) [1 + {2 tanh^2 (2 beta J) - 1} 2/pi K (xi^2 ) ],
$
with $K (xi^2 )$ defined as
$
  K (xi^2 ) eq.triple & integral_(0)^(pi/2)"d"theta" "(1 - xi^2 sin^2 theta)^(-1/2) \
$
and $xi$ defined as
$
  xi & eq.triple 2 tanh(2 beta J) / cosh(2 beta J) \
$
Setting $J = 1$ for our case thus yields
$
  epsilon (beta) &= - coth(2 beta) [1 + {2 tanh^2 (2 beta ) - 1} 2/pi K (xi^2 ) ],
$
with $K (xi^2 )$ remaining the same, but $xi$ losing its $J$ dependence
$
  xi & = 2 tanh(2 beta)/ cosh(2 beta) \
$

The lab manual also gives us the following expression for the absolute value of the expected magnetization
$
  abs(m (beta)) & = [1 - sinh (2 beta J)^(-4) ]^(1/8), \
$
which in the case of $J =1$ becomes
$
  abs(m (beta)) & = [1 - sinh (2 beta )^(-4) ]^(1/8). \
$
=== Implementation Details
The elliptical integral of the first kind involved in the analytical solution was solved numerically using AGM (arithmetic-geometric mean) methods (see https://en.wikipedia.org/wiki/Elliptic_integral).

Results are calculated for 200 temperature steps and printed to CSV file for every $L = [2, 5]$. Magnetization is set to zero for temperatures above the critical temperature (below the critical inverse temperature).

Further implementation details can be seen in the comments of the source code.
=== Results
Results were then plotted using a Matplot script written largely by Google Gemini.


#figure(
  image("./code/problem2/data/ising_phase_transition.png"),
  caption: [Plot of energy density and magnetization as a function of inverse temperature],
) <bruteforce_plot>

As seen in the above figures, the numerical results approach the analytical results with progressively increasing degrees of accuracy as $L$ is increased.

On the leftmost plot in figure @bruteforce_plot we see that increasing the size of the grid $L$ results in data that come continually closer to the expected solution, only differing slightly around $beta = 0.4$ .

The rightmost plot, on the other hand, shows that the numerically calculated expected value of the absolute value of the magnetization diverges significantly from the analytical solution below the critical inverse temperature, though we once again see that increasing $L$ results in a dramatic decrease of the error.

The plot of magnetization as a function of inverse temperature also shows that the expected value of the magnetization (not absolute magnetization) remains zero for all value of $L$ . This confirms that our program accurately considers every state and when added together the resulting magnetization will always be 0.

== Task 3
=== Part A
In Part A of Task 3 we are asked implement the multihit Metropolis algorithm for the two-dimensional Ising-Model in order to calculate energy density, magnetization, and specific heat as a function of temperature at $h = 0$ . We are told to use a grid of size $128 times 128$ and asked to find the optimal thermalization time and multihit parameters, specifically the number of sweeps $N_(t)$ and the number of multihits to perform per spin $N_("try")$ .

==== Theory

Implementing the multihit metropolis algorithm involves four main steps:
1. Creating an arbitrary grid of spins as a starting point.
2. Performing the necessary number of sweeps $N_(t)$ with the desired $beta$ for the given state to be uncorrelated with the previously measured state.
3. Measure the desired values for the given $beta$.
4. Repeat steps 2 and 3 for further desired values.

The details of performing a sweep are of course also important and can be roughly broken down into these simple steps:
1. Starting at the first spin in the grid, calculate the change in energy $Delta H$ that would occur from flipping the spin.
2. For every number of flip attempts $N_("try")$, always flip the spin if energy is reduced, otherwise have a small, temperature-dependent, non-zero probability $P_(i j)$  of flipping the spin.
3. Repeat steps 1 and 2 for every spin in the grid.

The probability $P_(i j)$ is defined as the probability of the grid changing from state $omega_(i)$ to $omega_(j)$ and is given by the expression

$
  P_(i j) =
  cases(
    exp [-beta (H (omega_(i) ) - H (omega_(j) ) ) ] & quad quad :H (omega_(i) ) >= H ( omega_(j) ),
    1 & quad quad :H (omega_(i) ) < H (omega_(j) )
        .
  )
$

Specific heat is given by the following set of relations:
$
  C_(v) & = pdv(expval(E), T) = 1 / (k_("B") T^2 ) expval((Delta E)^2), \
$
with $expval((Delta E)^2)$ defined as
$
  expval((Delta E)^2) & eq.triple expval((E - expval(E))^2) \
                      & = expval(E^2) - expval(E)^2. \
$

In our dimensionless simulation, $k_("B") = 1$ and $beta = 1 / (k_("B") T )$ , resulting in the equation
$
  C_(v) & = beta^2 expval((Delta E)^2) \
        & = beta^2 (expval(E^2) - expval(E)^2). \
$


==== Implementation Details

===== Selecting Efficient Starting Conditions

Though the starting conditions for the distribution of spins can in theory be arbitrary, the results will converge much faster if the distribution of spins is already close to the expected distribution for the given temperature $beta$ . In practice, this means that for low $beta$ (high temperature) there will be a "warm start" with the spins distributed more or less randomly. The arrangement of spins is the expected to get progressively more orderly as $beta$ increases (temperature decreases).

Fortunately, we progress through the temperatures progressively from low to high $beta$ . This means that the state $omega_(0)$  previously thermalized at $beta_(0)$ is very close to the desired thermalized state $omega_(1)$  at $beta_(1)$ ! Ergo, if we use $omega_(0)$ as our starting condition for the thermalization process at $beta_(1)$ our simulation will converge much faster than if we created a new random distribution every time.

===== Calculating $Delta H$

Though calculating the change in energy $Delta H$  initially seems like it may be computationally expensive, we only need to consider the change in energy caused by the interaction change between a single spin and its nearest neighbors each time. The calculation for this change is as follow:
$
  Delta E & = E_("new") - E_("old") \
          & = s_(x) dot S_("neighbors") - (- s_(x) dot S_("neigbors") ) \
          & = 2 s_(x) dot S_("neighbors"), \
$
where $S_("neighbors")$ simply denotes the sum of the four spins neighboring $s_(x)$ .

===== General
In order to get the most accurate possible results for the energy density, magnetization, and specific heat capacity, we first performed 2,000 "warmup" sweeps for every temperature and then averaged the values over 2,000 further sweeps.

==== Results
The first part of the assignment that we approach is the experimental search for the optimal number of sweeps $N_(t)$ and the optimal number of multihits to perform per spin location $N_("try")$.

This is realized by plotting energy density as a function of $N_(t)$ and $N_("try")$ for a variety of $beta$-values and observing how quickly the system converges to a stable state.

In practice, for a system of binary states like the Ising-Model, performing multiple hits only serves to undo any thermalization progress that has been made. This can be see in the below plots where runs with an even number of hits converge slower.

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.0.png", width: 80%),
  caption: [Thermalization at $beta = 0.0$ ],
) <beta0.0>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.1.png", width: 80%),
  caption: [Thermalization at $beta = 0.1$ ],
) <beta0.1>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.2.png", width: 80%),
  caption: [Thermalization at $beta = 0.2$ ],
) <beta0.2>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.3.png", width: 80%),
  caption: [Thermalization at $beta = 0.3$ ],
) <beta0.3>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.4.png", width: 80%),
  caption: [Thermalization at $beta = 0.4$ ],
) <beta0.4>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.5.png", width: 80%),
  caption: [Thermalization at $beta = 0.5$ ],
) <beta0.5>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.6.png", width: 80%),
  caption: [Thermalization at $beta = 0.6$ ],
) <beta0.6>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.7.png", width: 80%),
  caption: [Thermalization at $beta = 0.7$ ],
) <beta0.7>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.8.png", width: 80%),
  caption: [Thermalization at $beta = 0.8$ ],
) <beta0.8>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_0.9.png", width: 80%),
  caption: [Thermalization at $beta = 0.9$ ],
) <beta0.9>

#figure(
  image("./code/problem3/problem3_a/plots/plot_beta_1.0.png", width: 80%),
  caption: [Thermalization at $beta = 1.0$ ],
) <beta1.0>

As we previously noted, performing more than a single hit per spin does not consistently make the system converge faster, so all further measurements were performed with a single hit per spin.


#figure(
  image("./code/problem3/problem3_a/plots/plot_multibeta_thermalization.png"),
  caption: [Convergence of energy density as a function of numbers of sweeps for a variety of $beta$ values],
) <multi-beta>

If one looks careful in figure @multi-beta, one can see that the system undergoes convergence at high $beta$ values.


Though these plots are nice and provide a quick overview of how sweep index and the number of multihits affects the energy density, we decided that a 2D plot is more practical for making clear observations about the data, leading to our final plot for deciding thermalization parameters.

#figure(
  image("./code/problem3/problem3_a/plots/plot_2d_thermalization_lines.png"),
  caption: [2D Thermalization for multiple $beta$ values],
) <2d_multi-beta>

Zooming in on figure @2d_multi-beta for temperatures below which thermalization occurs, we get the following plot:

#figure(
  image(
    "./code/problem3/problem3_a/plots/plot_2d_thermalization_lines_reduced.png",
  ),
  caption: [2D Thermalization lines for $beta$ values equal to and above 0.4],
) <2d_multi-beta-reduced>

Looking at figure @2d_multi-beta-reduced, we see that the system reaches a semi-stable state after about 1,000 sweeps. For the sake of avoiding running the simulation for too short of a time, we elected to use 2,000 sweeps to maintain a large margin of error.

Now that we have determined the optimal number of sweeps and multihits to use for the simulation, we continue by calculating the values asked for in the lab: energy density, magnetization, and specific heat, all as a function of temperature with $h = 0$ .

#figure(
  image("./code/problem3/problem3_a_continued/plots/thermodynamics_L128.png"),
  caption: [Energy density, magnetization, and specific heat as a function of $beta$ ],
) <problem_3a>

Looking at the results of the simulation in figure @problem_3a, we see that the computational results very closely match the expected analytical results for energy density and magnetization,while specific heat curve matches what we see given in the lab manual.




=== Part B
In Part B of task 3 we are given $beta = 0.4406868$ and asked to determine the energy density, $expval(m)$, and $expval(m^2)$ with 200,000 sweeps on grids of size $L = {4, 8, 32}$ . We are asked to compare the $L = 4$ results with the exact predictions given in section 5.4 of the lab manual.


== Task 4
