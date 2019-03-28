#!/bin/bash

N=100
filas=10
columnas=10

for i in {1..50} do
	./traspuesta $filas $columnas $N
	N=$(($N+700)) >> traspuesta.log
done