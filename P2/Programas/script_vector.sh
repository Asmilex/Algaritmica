#!/bin/bash

mv vector.log vector_old.log
make clean
make

N=1000

# Parámetros: 0 -> Lineal, 1 -> DyV

DyV=1

echo \n\n\nDivide y vencerás activo: $DyV
for i in {1..50}; do
	for j in {1..3}; do
	    ./vector $N $DyV >> vector.log
	done

	N=$(($N+700))
done
