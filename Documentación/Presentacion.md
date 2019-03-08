# Presentación

## Algoritmo 4

### Teoría

Observamos que llamamos recursivamente a la función. Nuestro problema decrece en $n/2$ por cada llamada que hacemos a la función:
```
             |_|_|_|_|_|_|_|_|_|_|_|
------|      ^         ^          ^
Iter 1|  inicio       centro       final
------|      ^    ^    ^
Iter 2|  inicio   c    fin
------|
```

Definimos $T(n) = T(n/2)+a$, donde a es la constante asociada a las operaciones elementales.

Hacemos un cambio de variable $n = 2^k$. Se tiene entonces
$$T(2^k) = a + T(2^{k-1}) \\ T(2^{k-1}) = a + T(2^{k-2})
\\...\\
T(2^k) = a \cdot k + 1$$
Desaciendo el cambio de variable, obtenemos
$$T(n) = a \cdot log_2(n) + 1$$

Por tanto, concluimos que el algoritmo 4 es $O(log_2(n))$

## Algoritmo 5

### Teoría

