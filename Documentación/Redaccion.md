# Presentación

> Autores: Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

#### Introducción

En este documento recogeremos los datos de nuestras partes individuales y los compararemos. Asímismo, haremos un análisis de los algoritmos 4, 5 y 6, estudiando los diferentes efectos que producen en una específica máquina.

## Algoritmo 4

### Teórica

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

### Comparación empírica e híbrida

Tras los diferentes tests en nuestras respectivas máquinas, estos son los resultados que hemos obtenido:

![Gráficas]()

Podemos ver que el PC más rápido es el de TODO este PC tiene

## Algoritmo 5

### Teórica

### Comparación empírica e híbrida

Como en la anterior vez, ejecutamos los scripts cada uno por nuestra cuenta, y se han hallado los siguientes valores:

!(Gráficas)[]

## Algoritmo 6

### Teoría


## Comparación burbuja y mergesort

### Teórico

No hemos estudiado `mergesort` a nivel teórico. Sin embargo, tras los respectivos análisis hechos, podemos ver que la función es de tipo $O(sepadios)$. Comparándolo con `burbuja`, claramente vemos que TODO


### Empírico

### Híbrido


## Conclusiones
