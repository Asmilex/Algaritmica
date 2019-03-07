#!/bin/bash

for j in {1..13}; do
    N=100

    for i in {1..4}; do
        ./pivotajo $N >> resultados.txt
        N=$(($N*10))
    done
done

./pivotajo 500000 >> resultados.txt
./pivotajo 1000000 >> resultados.txt