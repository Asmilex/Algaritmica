#!/bin/bash

N=100

for j in {1..28}; do

    for i in {1..15}; do

        ./pivotajo $N >> resultados_buscarbinario.dat

    done

    N=$(($N+700))

done
