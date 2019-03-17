#!/bin/bash

N=100

for j in {1..28}; do

    for i in {1..40}; do
	
        ./BuscarBinario $N >> resultados_buscarBinario.dat
        
    done

    N=$(($N+70000))

done
