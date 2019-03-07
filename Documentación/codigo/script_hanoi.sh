#!/bin/bash

for j in {1..13}; do
    N=2

    for i in {1..5}; do
        ./hanoi $N >> resultados_hanoi.txt
        N=$(($N+7))
    done
done
