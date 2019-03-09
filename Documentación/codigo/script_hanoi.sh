#!/bin/bash

N=2

for j in {1..5}; do
	for i in {1..15}; do
		./hanoi $N >> resultados_hanoi.dat
	done

	N=$(($N+7))
done

