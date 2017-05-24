#b) en funcion de T
#for t in $(seq 1.6 0.01 10)
#do
#    ../bin/ising.e -t $t -n 32 >> datos.dat
#done

#b) correlaciones
#for T in $(seq 1.6 0.05 2.1)
#do
#    echo $T
#    ../bin/ising.e -T $T -n 32 -c -r 15 -i 8000
#done
#for T in $(seq 2.1 0.02 2.5)
#do
#    echo $T
#    ../bin/ising.e -T $T -n 32 -c -r 15 -i 8000
#done
#for T in $(seq 2.5 0.05 10)
#do
#    echo $T
#    ../bin/ising.e -T $T -n 32 -c -r 15 -i 8000
#done

#A) en funcion de T con B=1 y B=-1
#for T in $(seq 1.6 0.01 10)
#do
#    echo $T
#    ../bin/ising.e -T $T -n 32 -B 1 >> datos_B+.dat
#done
#
#for T in $(seq 1.6 0.01 10)
#do
#    echo $T
#    ../bin/ising.e -T $T -n 32 -B -1 >> datos_B-.dat
#done

#c) en funcion del tamanio
#for n in $(seq 4 4 28)
#do
#    for t in $(seq 1.6 0.01 10)
#    do
#        echo "$n $t"
#        ../bin/ising.e -T $t -n $n >> datos_$n.dat
#    done
#done
