#!/bin/bash

N=100

for i in {1..50} do
	./vector $N
	N=$(($N+700)) >> vector.log
done