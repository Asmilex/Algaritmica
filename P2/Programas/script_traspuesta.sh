#!/bin/bash
mv traspuesta.log traspuesta_old.log

make clean
make

filas=2
columnas=2
DyV=1

echo Divide y vencerás activo: $DyV
for i in {1..10}; do
    for j in {1..3}; do
	    ./traspuesta $filas $columnas $DyV >> traspuesta.log
    done

    filas=$((2*filas))
    columnas=$((2*columnas))
done
