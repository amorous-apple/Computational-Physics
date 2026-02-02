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
= Results
== Task 1
=== Part A
The first part of task 1 asks us to calculate $pi$ numerically through a Monte Carlo simulation involving the random distribution of points $(x,y)$ in the unit square.

The area of a circle is of course
$
  a & = pi r^2 \
$
and that of the unit square is 1. If we center a circle with radius 1 on the origin, then the fraction of the unit square covered by the circle $f$ is given by
$
       f & = (pi r^2) / 4 dot 1 / 1 = pi r^2 / 4 \
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
  pi & = (4 p) /q. \
$
To show convergence for this task with consistent results, a seed-based random number generator was used and the logarithm of percent error was plotted as a function of points used.

#figure(
  image("./code/problem1/part_a/convergence_plot.png"),
  caption: "Plot of Pi Approximation as a function of Points used",
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


The required normal distribution was realized by using two uniformly generated numbers and a Box-Muller transform. The two random numbers $x,y in (0, 1 ]$ were processed as follows:
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


== Task 2
== Task 3
== Task 4
