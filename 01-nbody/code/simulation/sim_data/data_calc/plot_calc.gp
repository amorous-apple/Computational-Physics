set terminal pngcairo size 700,700
set output "./2body_eulercrom_0.01_calc.png"
set datafile separator ","

plot '2body_eulercrom_0.01_calc.csv'