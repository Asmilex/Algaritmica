#!/bin/bash

for i in {1..15}; do
    touch resultados_hanoi_temp.dat
    ./mergesort resultados_hanoi_temp.dat 100 800 1500 2200 2900 3600 4300 5000 5700 6400 7100 7800 8500 9200 9900 10600 11300 12000 12700 13400 14100 14800 15500 16200 16900 17600 18300 19000
done

sort -n resultados_hanoi_temp.dat >> resultados_hanoi.dat
rm resultados_hanoi_temp.dat