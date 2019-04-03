#!/bin/bash
mv traspuesta.log traspuesta_old.log

make clean
make

N=100
filas=10
columnas=10

for i in {1..50}; do
    for j in {1..3}; do
	    ./traspuesta $filas $columnas $N >> traspuesta.log
    done	
    N=$(($N+700))
done
