# Parte individual

## Juan Antonio Villegas Recio

### Análisis teórico:

#### Algoritmo 1:

```c++
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
Si miramos el código de abajo arriba, la sentencia `return` y las sentencias `if` son todas de orden `O(1)`, luego su ejecución se puede considerar con una constante $a$.

Ahora veamos los bucles. Encontramos un bucle que anida a otros dos menores. Los bucles menores tienen un incremento y decremento respectivamente de una variable, y esa operación es `O(1)`, luego también se puede acotar mediante constantes $b_1$ y $b_2$. Además de estos dos bucles, el primero de todos incluye una sentencia `if` que también es constante, por lo que podemos acotarla mediante una constante $c$.

Ahora analicemos las iteraciones, con respecto a las iteraciones de los dos bucles internos, vemos que `i = ini + 1` y `j = fin`. Asumimos que `ini` y `fin`, en el peor de los casos, representarán el inicio y el final del vector; esto es, 0 y el tamaño del vector ($n$).
Los bucles se ejecutan mientras que `i <= j`. $i$ sólo cambia su valor si entra al primer bucle y $j$ si entra al segundo. En total, como ambos comparten la condición `i<=j`, en total entre los dos bucles hacen como máximo $n-1$ iteraciones (porque el valor inicial de $i$ es `ini+1`). Por tanto el cuerpo del bucle padre tarda en ejecutarse un tiempo lineal. Es decir,

$$\sum_{while\ 1}{b_1} + \sum_{while\ 2}{b_2} +c= fin - (inicio + 1) +c\sim n+c \Rightarrow O(n)$$

Volviendo al bucle inicial, tenemos que, en el peor de los casos:

$$\Big(\sum_{i \le j}{a\cdot (n+c)}\Big) + a= (fin - (inicio + 1))\cdot (n+c) + a \sim n^2 + c_*n +a \Rightarrow O(n^2)$$

Donde he acotado las operaciones en las que interviene la constante $c$ por otra constante $c_*$, ya que a efectos prácticos no es relevante su valor.

Concluimos entonces que la función es $O(n^2)$



#### Algoritmo 2:

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

Tanto la declaración de las variables, como la sentencia `if`, como la sentencia `return` son `O(1)` y por tanto constantes. La clave está en hallar la eficiencia del bucle `while` interno.

El cuerpo del bucle while se compone de una sentencia `O(1)` y de una sentencia condicional. Como sentencia condicional que es, su eficiencia es el máximo del cuerpo del `if` y el cuerpo del `else`, pero como ambas son constantes, concluimos que el cuerpo completo del bucle es `O(1)` y se puede acotar por una constante $a$.

Veamos cuantas veces se itera este bucle. En el peor de los casos, no se encuentra el elemento que se busca, luego se itera hasta que `inicio<=fin`. En cada iteración se considera un vector de tamaño la mitad que el anterior, luego, en la iteración $k$:

$$T(n) = n \cdot \Big( \frac{1}{2}\Big)^{k}  = 1$$

Multiplicando por $2^k$ y aplicando el cambio de variable $n=2^k$ tenemos:

$$2^k \cdot n \cdot \Big( \frac{1}{2} \Big)^{k}  = 2^k \iff n = 2^k \iff log_2(n) = k$$

Por tanto este algoritmo es de orden $O(\log_2(n))$.



#### Algoritmo 3:

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

Si miramos el código de abajo arriba, el bucle más interno es el `for` anidado en un bucle `do-while`. Anida una sentencia de asignación, que es `O(1)`, por ello se acota mediante una constante $a$. Las demás sentencias son también declaraciones de variables, asignaciones, incrementos o decrementos, que en todo caso son contantes `O(1)`.

El bucle `do-while` anida una sentencia condicional, por lo que la eficiencia de ese bucle será el máximo de los cuerpos del `if` y el `else`. El if anida un bucle, y el `else` un incremento, por lo que claramente la eficiencia de ese bloque será la del `if`, es decir, la del bucle.

Si nos fijamos en las iteraciones, el bucle `for` interno se ejecuta, si llamamos, por comodidad `n:=nOriginal`, $(n-1)-(j+1)+1=a\cdot(n-j-1)$ veces. Teniendo en cuenta los intervalos de los bucles tenemos una fórmula como la siguiente:

$$\sum_{i=0}^{n-1}\Big(\sum_{j=i+1}^{n-1}\Big(\sum_{k=j+1}^{n-1}\Big(a\Big)\Big)\Big)=\sum_{i=0}^{n-1}\Big(\sum_{j=i+1}^{n-1}\Big(a(n-j-1)\Big)\Big)$$

Si desarrollamos las sumatorias:

$$a\sum_{j=i+1}^{n-1}\Big(n-j-1\Big)=a((n-i-2)+(n-i-3)+\cdots+(n-(n-1)-1))=$$
$$a((n-1-i)(n-i)-p_1(i,n))$$
Donde $p_1(i,n)$ es una constante que depende del valor de $i$ y de $n$ que no es relevante para hallar la eficiencia.

$$a\sum_{i=0}^{n-1}\Big((n-1-i)(n-i)-p_1(i,n)))=a\sum_{i=0}^{n-1}\Big(n^2+p_2(i,n)\Big)=$$
$$n^2+p_2(0,n)+n^2+p_2(1,n)+\cdots+n^2+p_2(n-1,n)\sim n(n^2+p_3(i,n))\sim n^3$$

Donde $p_2(i,n)$ y $p_3(i,n)$ son polinomios en $n$ de grado menor o igual que 2, por ello no tienen relevancia al calcular la eficiencia teórica del algoritmo.

Podemos concluir que el algoritmo es $O(n^3)$