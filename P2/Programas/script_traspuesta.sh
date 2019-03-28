#!/bin/bash

N=100

for i in {1..50} do
	./traspuesta $N
	N=$(($N+700)) >> traspuesta.log
done