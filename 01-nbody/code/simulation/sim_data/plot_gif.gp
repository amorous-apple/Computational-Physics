set term gif animate delay 2 size 400, 400
set output "animation.gif"
set datafile separator ","

stats '1kbody_1_0.01.csv' us 2 name "x" nooutput
stats '1kbody_1_0.01.csv' us 3 name "y" nooutput
stats '1kbody_1_0.01.csv' us 4 name "z" nooutput

set xlabel "x"
set ylabel "y"
set zlabel "z"
set xrange [x_min-.1:x_max+.1]
set yrange [y_min-.1:y_max+.1]
set zrange [z_min-.1:z_max+.1]

do for [i=0:int(x_blocks-2)] {
	splot '1kbody_1_0.01.csv' us 2:3:4 index i w p pt 7 title "t: ".(i)
}
