#!/bin/bash

mv vector.log vector_old.log
make clean
make

N=1000

for i in {1..50}; do
	./vector $N >> vector.log
	#N=$(($N+700))
done