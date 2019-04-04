# Presentación grupal

Autores:

> Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

## Especificaciones

| Persona      | CPU              | OS                   |
| ------------ | ---------------- | -------------------- |
| Ana          | i5-6200U 2.30GHz | Ubuntu 16.04 LTS     |
| Andrés       | i5-8250U 3.40GHz | Antergos 4-19.29 LTS |
| Paula        | i7-5600U 2.60GHz | Ubuntu 18.04 LTS     |
| Juan Antonio | i7-4500U 3.00GHz | Ubuntu 18.04 LTS     |

## Objetivos

- Resolver dos problemas con la metodología Divide y Vencerás
- Exponer los tres tipos de eficiencia

### Problema asignado: Máximo y mínimo de un vector

Para este problema, hemos pensado en aplicar una filosofía al mergesort: subdividir el vector en dos partes y obtener el máximo (resp. mínimo) de cada subvector para después compararlos y devolver el máximo (resp. mínimo).

#### Código

```c++
int maximo (vector<int> &flechita, int l, int r) {
    if(l<=r){

        if (r - l <= 1) {
            if (flechita[l] < flechita[r])
                return flechita[r];
            else
                return flechita[l];
        }

        else {
            int m    = (l + r)/2;
            int maxL = maximo(flechita, l, m);
            int maxR = maximo(flechita, m + 1, r);

            if (maxL < maxR)
                return maxR;
            else
                return maxL;
        }

    }
}

int minimo (vector<int> &flechita, int l, int r) {
    if(l<=r){

        if (r - l <= 1) {
            if (flechita[l] > flechita[r])
                return flechita[r];
            else
                return flechita[l];
        }

        else {
            int m    = (l + r)/2;
            int minL = minimo(flechita, l, m);
            int minR = minimo(flechita, m + 1, r);

            if (minL < minR)
                return minL;
            else
                return minR;
        }

    }
}
```

#### Análisis teórico

Analizamos la eficiencia teórica de la función `maximo`, ya que la otra es análoga. La función es recursiva, luego necesitamos una ecuación de recurrencia para plantearlo. Si el tamaño del vector a buscar es 2 o menos, tenemos un bloque `if-else` cada uno con una sentencia de tiempo constante, luego este caso se puede acotar con una constante $a$. El caso en el que el tamaño sea mayor que 2, hay dos llamadas a la propia función pero el tamaño es de la mitad junto con un conjunto de sentencias que se pueden acotar por una constante $b$. Resumiendo:

$T(n)=a$      si  $n\leq 2$

$T(n)=T(\frac{n}{2})+b$     si $n>2$

Resolvamos la recurrencia. Para ello, hacemos el cambio de variable $n=2^k$, y denotamos $T(2^k)=t_k$ por lo que entonces quedaría la segunda ecuación como: $t_k=2t_{k-1}+b$. Y resolvemos esta ecuación de recurrencia.

Primero calculamos la solución de la homogénea asociada: $t_{k+1}-2t_k=0$

La ecuación característica es $x-2=0$, por lo que su única solución es $x=2$, por tanto la solución a la ecuación homogénea es: $t_k^h=c_1\cdot 2^k$ siendo $c_1$ una constante que depende del valor inicial.

Calculamos ahora una solución particular, que sería una solución constante, que denotamos por $t_k^p$. Se tiene que $t_k^p- 2t_k^p-b=0$, despejamos y nos queda $t_k^p=-\frac{b}{2}=c_2$, que denotaremos como $c_2$ porque es otra constante.

En conclusión: $t_k=t_k^h +t_k^p=c_1\cdot 2^k+c_2$, y deshaciendo el cambio de variable, obtenemos $T(n)=c_1\cdot n+c_2$. Observando la ecuación, concluimos que el algoritmo es de orden $O(n)$.



