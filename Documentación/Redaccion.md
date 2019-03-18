# Presentación

> Autores: Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

#### Introducción

En este documento recogeremos los datos de nuestras partes individuales y los compararemos. Asímismo, haremos un análisis de los algoritmos de búsqueda binaria, ordenación por heapsort y ordenación por mergesort, estudiando los diferentes efectos que producen en una específica máquina.

## Especificaciones

| Persona      | CPU               | OS                    |
|--------------|-------------------|-----------------------|
| Ana          | i5-6200U 2.30GHz  | Ubuntu 16.04 LTS      |
| Andrés       | i5-8250U 3.4GHz   | Antergos 4-19.29 LTS  |
| Paula        | i7-5600U 2.60GHz  | Ubuntu 18.04 LTS      |
| Juan Antonio | i7-4500U 3.00GHz  | Ubuntu 18.04 LTS      |

## Algoritmo 4 - BuscarBinario

Código del programa

```c++
    int BuscarBinario (int *v, const int ini, const int fin, const double x) {
        int centro;

        if (ini > fin)
            return -1;

        centro = (ini + fin)/2;

        if (v[centro] == x)
            return centro;

        if (v[centro] > x)
            return BuscarBinario(v, ini, centro-1, x);

        return BuscarBinario (v, centro+1, fin, x);
    }
```

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

![Gráficas](./graficas/BuscarBinario_grupo_datos.png)

Podemos ver que el PC más rápido es el de Andrés en media, tardando 350ns como máximo.

## Algoritmo 5 - Heapsort

Código del programa:

```c++
void reajustar (int T[], int num_elem, int k) {
    int j, v;
    bool esAPO = false;

    v = T[k];

    while ( (k < num_elem/2) && !esAPO ) {
        j = k + k + 1;

        if ( j < (num_elem - 1) && T[j] < T[j+1] )
            j++;

        if (v >= T[j])
            esAPO = true;

        T[k] = T[j];
        k = j;
    }

    T[k] = v;
}

void heapsort (int T[], int num_elem) {
    int i;

    for (i = num_elem/2; i >= 0; i--)
        reajustar(T, num_elem, i);

    for (i = num_elem - 1; i >= 1; i--) {
        int aux = T[0];

        T[0] = T[i];
        T[i] = aux;
        reajustar(T, i, 0);
    }
}
```


### Teórica

Primero estudiaremos la eficiencia de `Reajustar`. En cada iteración, la variable `k` se multiplica por 2.

En el peor de los casos, en la función reajustar, el número debe ser llevado desde lo alto del heap hasta las hojas más bajas. Así, la cantidad de datos movidos no es más grande que

$$\sum_{N \geq i \geq 1}{log_2(N/i)} + \sum_{N \geq i \geq 1}{log_2(i)} = N * log_2(N) + O(N)$$

### Comparación empírica e híbrida

Como en la anterior vez, ejecutamos los scripts cada uno por nuestra cuenta, y se han hallado los siguientes valores:

![Gráfica Heapsort](./graficas/heapsort_grupo_datos.png)

## Hanoi

Código del programa:

```c++
void hanoi (int M, int i, int j) {
    if (M > 0) {
        hanoi(M-1, i, 6-i-j);
        //cout << i << " -> " << j << endl;
        hanoi (M-1, 6-i-j, j);
    }
}
```

### Comparativa empírica

Mostramos de nuevo todos los resultados en una misma gráfica:

![Gráfica Hanoi](./graficas/hanoi_grupo_datos.png)

## Burbuja

Código del programa:

```c++
void burbuja (int T[], int inicial, int final) {
        int i, j, aux;

        for (i = inicial; i < final - 1; i++) {
            for (j = final - 1; j > i; j--) {
                if (T[j] < T[j-1]) {
                    aux = T[j];
                    T[j] = T[j-1];
                    T[j-1] = aux;
                }
            }
        }
    }
```

### Comparativa empírica

Aquí mostramos las gráficas respectivas de los valores obtenidos para burbuja y la regresión para cada persona del grupo:

![Gráfica BurbujaDatos](./graficas/burbuja_grupo_datos.png)

![Gráfica Burbuja - Regresion](./graficas/burbuja_grupo_regresion.png)


## Comparación burbuja y mergesort

### Teórico

No hemos estudiado `mergesort` a nivel teórico. Sin embargo, tras los respectivos análisis hechos, podemos ver que la función es de tipo $O(nlog2(n))$. En comparación con `burbuja`, claramente vemos que tiene que ser más eficiente `mergesort`, dado que $O(nlog_2(n)) \subset O(n^2)$

### Empírico

### Híbrido


## Conclusiones
