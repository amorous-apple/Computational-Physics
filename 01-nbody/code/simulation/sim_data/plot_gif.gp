set term gif animate delay 2 size 400, 400
set output "animation.gif"
set datafile separator ","

stats '3body_1_0.01.csv' us 2 name "x"

set xlabel "x"
set ylabel "y"
set zlabel "z"
set xrange [-2:2]
set yrange [-2:2]
set zrange [-2:2]

do for [i=0:int(x_blocks-2)] {
	splot '3body_1_0.01.csv' us 2:3:4 index i w p pt 7 title "t: ".(i)
}
