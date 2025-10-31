#!/usr/bin/env zsh

# for FILE_BASE in 2body 3body; do
#     for INTEGRATOR in euler eulercrom velver mid velver hermite hermite_it; do
#         for TIMESTEP in 0.5 0.01; do
for FILE_BASE in 2body 3body 100body 1kbody; do
    for INTEGRATOR in euler eulercrom velver hermite hermite_it heun; do
        for TIMESTEP in 0.01 0.1 0.5; do
            echo $FILE_BASE $INTEGRATOR $TIMESTEP
            ./simulate.out $FILE_BASE $INTEGRATOR $TIMESTEP
        done
    done
done
