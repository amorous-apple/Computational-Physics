set term gif animate delay 2 size 400, 400

basename = "3body_hermite_0.1"
timeStep = 0.1

set output "./animations/".basename.".gif"
set datafile separator ","

filename = "./data_system/".basename.".csv"

stats filename us 2 name "x" nooutput
stats filename us 3 name "y" nooutput
stats filename us 4 name "z" nooutput

set xlabel "x"
set ylabel "y"
set zlabel "z"
set xrange [x_min-.1:x_max+.1]
set yrange [y_min-.1:y_max+.1]
set zrange [z_min-.1:z_max+.1]

do for [i=0:int(x_blocks-2)] {
	splot filename us 2:3:4 index i w p pt 7 title sprintf("t: %.2f", i * timeStep)
}
