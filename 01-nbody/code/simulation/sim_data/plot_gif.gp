set terminal gif animate delay 5
set output "animation.gif"

set xlabel "x"
set ylabel "y"
set zlabel "z"
set xrange [-1:1]
set yrange [-1:1]
set zrange [-1:1]

do for [i=0:200] {
	splot '2body_2_0.01.csv' index i using 2:3:4 with points pointtype 7 title sprintf("t: %.4f", i * 0.01)
}
