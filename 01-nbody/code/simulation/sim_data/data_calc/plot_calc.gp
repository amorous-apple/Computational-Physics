set terminal pngcairo size 700,700 noenhanced
set datafile separator ","

basename = "100body_euler_0.1"
filename = "./".basename."_calc.csv"

# plotting angular moment as a function of time
set output "./".basename."_ang.png"
set title basename." Angular Momentum"
set xlabel 'Relative Time'
set ylabel 'Angular Momentum'
set grid
plot filename using 1:2 with lines title 'Angular Momentum'

#plotting energy as a function of time
set output "./".basename."_ener.png"
set title basename." Energy"
set xlabel 'Relative Time'
set ylabel 'Energy'
set grid
plot filename using 1:3 with lines title 'Energy'
