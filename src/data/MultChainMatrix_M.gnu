datafile = "data_M.txt"  
set output "graph_M.jpg"  
set grid
set xlabel "M"  
set ylabel "Time(ms)"
set xrange [5:80]
set xtics 5
set key outside bottom
set style line 1 lt 2 lw 3
set key box linestyle 1
plot datafile using 1:2 title "Opt(n=5)" with lines,datafile using 1:3 title "notOpt(n=5)" with lines,\
datafile using 1:6 title "Opt(n=15)" with lines,datafile using 1:7 title "notOpt(n=15)" with lines,\
datafile using 1:10 title "Opt(n=25)" with lines,datafile using 1:11 title "notOpt(n=25)" with lines,\
datafile using 1:14 title "Opt(n=35)" with lines,datafile using 1:15 title "notOpt(n=35)" with lines