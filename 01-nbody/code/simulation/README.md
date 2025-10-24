# N-body Simulation

This project runs an n-body simulation on the chosen data-set (2, 3, 100, or 1 000 bodies) with the chosen integrator (euler, rk4, etc.), and the chosen timestep (in seconds).

## Build instructions

- Install **nix** on your unix machine (use the package manager of choice for your system)
- Run `nix develop` to download the necessary dependencies and enter the dev-shell
- Run `make` to build the project
- Run a single simulation with `./simulate.out` and follow the directions, or edit and run `run.sh` to run multiple simulations
- Check/ plot data from the `data` directories

## Development

- (Optional) Run `bear -- make` if you add any new functions so that their definitions are added to the compilation database (allows LSP definition search)
