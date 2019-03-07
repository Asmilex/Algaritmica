# Parte individual

> Autor: Andrés Millán Muñoz

## Pivotar

Código del programa:

```C++
int pivotar (int *v, const int ini, const int fin) {
    double pivote = v[ini], aux;
    int   i = ini + 1
        , j = fin;

    while (i <= j) {
        while (v[i] < pivote && i <= j)
            i++;

        while (v[j] >= pivote && j >= i)
            j--;

        if (i < j) {
            aux = v[i];
            v[i]  = v[j];
            v[j]  = aux;
        }
    }

    if (j > ini) {
        v[ini] = v[j];
        v[j]   = pivote;
    }

    return j;
}
```

### Análisis teórico

Observamos que la mayoría de operaciones son constantes. Tanto las asignaciones y las operaciones son `O(1)`, así que no influirán en nuestros cálculos. Como estamos hayando la notación O(), nos pondremos siempre en el peor de los casos.

Sea $a$ la constante que acota las operaciones más básicas del bucle padre, $b$ las operaciones realizadas por el segundo `while` y $c$ por las del tercero.

Debemos analizar los bucles del algoritmo. Vemos que `i = ini + 1` y `j = fin`. Asumamos que `ini` y `fin` adquirirán los máximos valores posibles; esto es, 0 y el tamaño del vector respectivamente.
Nuestro primer bucle se ejecuta mientras que `i <= j`. Ambos valores solo pueden cambiar si entran en alguno de los dos bucles centrales. Además, uno retrocede y otro avanza. Debido a que en ambos se haya la condición `i<=j`, la suma de las ejecuciones de ambas debe ser como máximo `O(n)`. Esto es,

$$\sum_{while\ 1}{b} + \sum_{while\ 2}{c} = fin - (inicio + 1) \sim n \Rightarrow O(n)$$

Volviendo al bucle inicial, tenemos que

$$\Big(\sum_{i \le j}{a}\Big) + n = fin - (inicio + 1) + n \sim 2n \Rightarrow O(2n) = O(n)$$

Concluimos entonces que la función es $O(n)$

## Búsqueda

Código del programa:

```c++
int Busqueda (int * v, int n, int elem) {
    int   inicio = 0
        , fin    = n - 1
        , centro = (inicio + fin)/2;

    while ((inicio <= fin) && (v[centro] != elem)) {
        if (elem < v[centro])
            fin = centro - 1;
        else
            inicio = centro + 1;

        centro = (inicio + fin)/2;
    }

    if (inicio > fin)
        return -1;

    return centro;
}
```

### Análisis teórico

Supongamos que `v` es un vector de `n` componentes. Las operaciones elementales son constantes, por lo que estarán acotadas por una constante. Sea $a$ dicha constante.
En este algoritmo, por cada iteración, consideraremos un subvector ordenado del original de tamaño la mitad que el anterior. En el peor de los casos, existen dos posibilidades:

- Se halla en el último subvector posible. Este tiene 1 sola componente
- No se encuentra el elemento.

Ambos casos pueden considerarse el mismo, pues solo los diferencia una iteración. Por tanto, tenemos que
$$T(n) = n \cdot \Big( \frac{1}{2}\Big)^{k}  = 1$$
donde $k$ es la iteración.
$$2^k \cdot n \cdot \Big( \frac{1}{2} \Big)^{k}  = 2^k \iff n = 2^k \iff log_2(n) = k$$

Se tiene entonces que la eficiencia del algoritmo es $O(log_2(n) + a) \sim O(log_2(n))$.

## Elimina repetidos

Código del programa:

```c++
void EliminaRepetidos (int original[], int & nOriginal) {
    int i, j, k;

    for (i = 0; i < nOriginal; i++) {
        j = i + 1;

        do {
            if (original[j] == original[i]) {
                for (k = j+1; k < nOriginal; k++)
                    original[k-1] = original[k];

                nOriginal--;
            }
            else
                j++;

        } while (j < nOriginal);
    }
}
```

### Análisis teórico
