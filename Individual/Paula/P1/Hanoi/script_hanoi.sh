#!/bin/bash

N=2

for j in {1..28}; do
	for i in {1..25}; do
		./hanoi $N >> resultados_hanoi.dat
	done

	N=$(($N+1))
done

