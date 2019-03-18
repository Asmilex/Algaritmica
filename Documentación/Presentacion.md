# Algarítmica

Autores:

> Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

---

## Objetivos

- Solucion teorica de los algoritmos 4, 5 y 6
- Comparación eficiencia empírica e híbrida de 4 y 5
- Comparar burbuja y mergesort

---

## Especificaciones

| Persona      | CPU               | OS                    |
|--------------|-------------------|-----------------------|
| Ana          | i5-6200U 2.30GHz  | Ubuntu 16.04 LTS      |
| Andrés       | i5-8250U 3.4GHz   | Antergos 4-19.29 LTS |
| Paula        | i7-5600U 2.60GHz  | Ubuntu 18.04 LTS      |
| Juan Antonio | i7-4500U 3.00GHz  | Ubuntu 18.04 LTS      |

---

## Algoritmo 4

#### BuscarBinario

```txt
             |_|_|_|_|_|_|_|_|_|_|_|
------|      ^         ^          ^
Iter 1|  inicio       centro       final
------|      ^    ^    ^
Iter 2|  inicio   c    fin
------|
```

Decrece en $n/2$. Resolvemos

---

Cambio de variable $n = 2^k$

$$T(2^k) = a + T(2^{k-1})$$
$$T(2^{k-1}) = a + T(2^{k-2})$$
...
$$T(2^k) = a \cdot k + 1$$

Desaciendo el cambio de variable, obtenemos

$$T(n) = a \cdot log_2(n) + 1$$

---

**BuscarBinario** es $O(log_2(n))$

---

## Comparativas empíricas y híbridas

![Gráficas]()