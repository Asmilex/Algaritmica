#!/bin/bash

for j in {1..10}; do
    N=100

    for i in {1..24}; do
        ./pivotajo $N >> resultados.txt
        N=$(($N+20000))
    done
done

#./pivotajo 500000 >> resultados.txt
#./pivotajo 700000 >> resultados.txt
#./pivotajo 1000000 >> resultados.txt
