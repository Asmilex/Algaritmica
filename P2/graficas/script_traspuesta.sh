#!/bin/bash
mv traspuesta.log traspuesta_old.log

make clean
make

N=100
filas=2
columnas=1

for i in {1..10}; do
    for j in {1..3}; do
	    ./traspuesta $filas $columnas >> traspuesta.log
    done	
    filas=$((2*filas))
    #columnas=$((2*columnas))
done
