# Algarítmica

## Eficiencia teórica del algoritmo 4

### Código

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

### Cálculo de la eficiencia teórica

El algoritmo `BuscarBinario` es recursivo, es decir, la eficiencia teórica se obtendrá mediante una recurrencia.

En cada ejecución de la función asumiremos que se tarda un tiempo constante $c$ salvo en el caso base, que se tarda $1$.

La recurrencia a resolver es:

$$T(n)=c+T(\frac{n}{2})$$

Realizando el cambio de variable $n=2^k$:

$$T(2^k)=c+T(\frac{2^k}{2})$$

$$T(2^k)=c+T(2^{k-1})$$

Así, tenemos una recurrencia aritmética sobre $k$, por lo tanto la solución es:

$$T(2^k)=c\cdot k +1$$

donde el 1 corresponde al tiempo empleado en el caso base.

Deshaciendo el cambio de variable anterior $n=2^k$ obtenemos:

$$T(n)=c\cdot \log_2{n} +1$$

Luego hemos obtenido así que la eficiencia teórica del algoritmo es $O(\log_2{n})$.