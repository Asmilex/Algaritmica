#!/bin/bash

mv ../Data/Logs/contenedor.log >> ../Data/Logs/contenedor_old.log

make clean
make

N=50
time=1

echo Modo benchmark activo: $time

for i in {1..25}; do
	for j in {1..50}; do
	    ./contenedores $N $time >> ../Data/Logs/contenedor.log
	done

	N=$(($N+50))
done
