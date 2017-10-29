datafile = "data_N.txt"  
set output "graph_N.jpg"  
set grid
set xlabel "N"  
set ylabel "Time(ms)"
set xrange [5:80]
set xtics 5
set key outside bottom
set style line 1 lt 2 lw 3
set key box linestyle 1
plot datafile using 1:2 title "Opt(m=5)" with lines,datafile using 1:3 title "notOpt(m=5)" with lines,\
datafile using 1:6 title "Opt(m=15)" with lines,datafile using 1:7 title "notOpt(m=15)" with lines,\
datafile using 1:10 title "Opt(m=25)" with lines,datafile using 1:11 title "notOpt(m=25)" with lines,\
datafile using 1:14 title "Opt(m=35)" with lines,datafile using 1:15 title "notOpt(m=35)" with lines