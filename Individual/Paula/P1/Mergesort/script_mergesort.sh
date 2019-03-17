#!/bin/bash

N=100

for j in {1..28}; do

    for i in {1..15}; do
	
        ./mergesort resultados_mergesort.dat `date +%s` $N
	cat resultados_mergesort.dat >> resultados.dat
        
    done

    N=$(($N+700))

done
