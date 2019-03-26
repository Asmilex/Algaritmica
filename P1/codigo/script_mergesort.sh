#!/bin/bash

N=100

for j in {1..28}; do

    for i in {1..15}; do
	
        ./mergesort `date +%s` $N >> resultados_mergesort.dat
        
    done

    N=$(($N+700))

done
