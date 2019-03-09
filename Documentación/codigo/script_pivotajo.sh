#!/bin/bash

N=100

for j in {1..5}; do

    for i in {1..15}; do
	
        ./pivotajo $N >> resultados_burbuja.dat
        
    done

    N=$(($N+700))

done
