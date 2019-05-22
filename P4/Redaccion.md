# Práctica 4. Programación dinámica

Grupo: Las Algas
> Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

## Objetivos

- Comprender el enfoque de la programación dinámica
- Identificar los elementos característicos en un problema concreto.
- Calcular la subsecuencia de caracteres común más larga dadas dos cadenas.
- Resolver dicho problema aplicando este método de programación

## Subsecuencia de caracteres más larga

### Enunciado

Sean dos secuencias de caracteres $X= (x_1, x_2, \dots , x_m)$ e $Y= (y_1, y_2, \dots , y_n)$, de longitudes $m$ y $n$ respectivamente. El problema consiste en encontrar la máxima subsecuencia de caracteres común que aparecen en ambas cadenas de izquierda a derecha (no necesariamente de forma contigua). Por ejemplo, para  las cadenas `S= "ABAZDC"` y `T= "BACBAD"`, la máxima subsecuencia común tiene longitud 4 y es `"ABAD"`, siendo localizadas en `S= "ABAZDC"` y en `T= "BACBAD"`.

### Solución

La solución que proponemos se basa en examinar el último carácter de ambas cadenas, si coincide lo añadimos a la solución, si no, lo descartamos primero de una cadena y luego de la otra, dividiendo el problema en dos ramas y buscamos una cadena común en cada una de ellas repitiendo el proceso. Por ejemplo, sean X="casa" e Y="cosa". Tenemos:

`LCS("casa", "cosa") = LCS("cas","cos")+a`​, ya que ambas tienen la última letra, calculamos ahora:

`LCS("cas","cos") = LSC("ca","co") + s​`, de nuevo porque comparten la última letra, a continuación:

`LCS("ca","co") = max(LCS("c","co"), LCS("ca","c"))`​, pues las letras finales son distintas.

`LCS("c","co") = max(LCS(" ","co"), LCS("c","c"))="c"​`

`LCS("ca","c") = max(LCS("c","c"), LCS("ca"," "))="c"​`

Recomponiendo las sucesivas recursiones obtenemos que el resultado es "csa​".

Por tanto, la recurrencia que define nuestro algoritmo si tenemos $X[0..n]$ e $Y[0..m]$ es:

$$LCS(X[0..n],Y[0..m])=\begin{cases}LCS(X[0..n-1],Y[0..m-1])+X[m-1] \quad\quad\quad\quad\quad\quad\quad\quad\quad \text{si }X[n-1]=Y[m-1] \\\max(LCS(X[0..n-1],Y[0..m]),LCS(X[0..n],Y[0..m-1])) \quad \text{  en otro caso}\end{cases}$$

Para agilizar los cálculos hemos tratado con una matriz de costos $M​$ que contiene la longitud de la mayor subsecuencia común entre los prefijos de $X​$ e $Y​$. El elemento $m_{ij}​$ representa la longitud de la subsecuencia común más larga de $X[0..i-1]​$ e $Y[0..j-1]​$.

En el ejemplo de $X​$="casa"​ e $Y​$="cosa" tenemos la matriz:

$A=\begin{pmatrix}\mathbf{1} & 1 & 1 & 1 \\ 1 & 1 & 1 & \mathbf{2} \\ 1 & 1 & \mathbf{2} & 2 \\ 1 & 1 & 2 & \mathbf{3} \end{pmatrix}​$

Señalamos en negrita las entradas en las que $X[i-1]=Y[j-1]​$. Para realizar el algoritmo, comenzamos a recorrer la matriz por la esquina inferior derecha. Si $X[i-1]=Y[j-1]​$, se añade a la solución este carácter, y si no lo son, nos movemos hacia arriba o hacia la izquierda, dependiendo de qué entrada sea mayor.

### Implementación

Consideramos la matriz de costos como global, y diseñamos una función que inicialice la matriz de acuerdo al criterio que describimos en el párrafo anterior, el pseudocódigo es el siguiente:

```py
LCS_coste (cadena X, cadena Y, entero m, entero n) {
    para cada 0 <= i < m
        para cada 0 <= j < n
            si coincide el carácter:
                costos[i+1][j+1] = costos[i][j]+1
            si no:
                costos[i+1][j+1] = max(costos[i][j+1], costos[i+1][j])
}
```

Y una vez tenemos la matriz de costos completa, entonces podemos llamar a la función que calcula la subsecuencia común más larga, de acuerdo al algoritmo propuesto:

```py
cadena LCS ( cadena X, cadena Y, entero m, entero n) {
    si alguna cadena esta vacía:
        devolver cadenavacía
    si coincide el último carácter:
        devolver LCS (X,Y,m-1,n-1)+último carácter
    si costos[m-1][n] >= costos[m][n-1]
        devolver LCS(X,Y,m-1;n)
    si no:
        devolver LCS(X,Y,m,n-1)
}
```

#### Implementación en C++

Si implementamos nuestro pseudocódigo en C++, empleamos una constante `MAX` que nos indicará el tamaño de las cadenas empleadas y declaramos la matriz de costos como global:

```c++
int costos[MAX][MAX];
```

Diseñamos también una función que genere cadenas de forma aleatoria:

```c++
string random_string(string::size_type length) {
    static auto& chrs = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static mt19937 rg{random_device{}()};
    thread_local static uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    string s;

    s.reserve(length);

    while(length--)
        s += chrs[pick(rg)];

    return s;
}
```

Y por último, presentamos las implementaciones de las funciones descritas en el pseudocódigo anterior:

```c++
void LCS_coste (string X, string Y, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (X[i] == Y[j])
				costos[i+1][j+1] = costos[i][j] + 1;
			else
				costos[i+1][j+1] = max(costos[i][j+1], costos[i+1][j]);
		}
	}
}
```

```c++
string LCS (string X, string Y, int m, int n) {
	if (m == 0 || n == 0)
		return string("");

	if (X[m - 1] == Y[n - 1])
		return (LCS(X, Y, m - 1, n - 1) + X[m - 1]);

	if (costos[m - 1][n] >= costos[m][n - 1])
		return LCS(X, Y, m - 1, n);
	else
		return LCS(X, Y, m, n - 1);
}
```

#### Ejemplo de ejecución

Veamos cómo reacciona el programa al ejecutar nuestro ejemplo: `X="casa"`, `Y="cosa"`.

<p style="text-align:center;"><img src="./Imagen/CasaCosaEjecucion.png" alt="Casa cosa ejecución"></p>


Como vemos, la matriz de costos coincide totalmente con la matriz planteada anteriormente, así como el resultado de la ejecución.

Si tomamos un ejemplo de longitud mayor, por ejemplo, con dos cadenas generadas aleatoriamente con 16 caracteres cada una, el resultado que obtenemos es el siguiente:

<p style="text-align:center;"><img src="./Imagen/EjemploGrande.png" alt="Matriz"></p>

De nuevo, podemos comprobar que la matriz es correcta y que la subsecuencia común más larga es la obtenida como resultado.

## Conclusiones

* La programación dinámica en este caso tiene ciertos elementos comunes con Divide y Vencerás, ya que ayuda a solucionar un problema grande mediante la resolución de subproblemas de menor tamaño.
* El cálculo de la matriz de costos nos ahorra muchas operaciones repetidas, por lo que ayuda a mejorar la eficiencia.
* La matriz de costos además ayuda a que la resolución del problema se reduzca a un simple recorrido por la matriz añadiendo a la solución los caracteres correctos.
* La recurrencia puede resultar compleja cuando el tamaño de las cadenas es grande y tienen pocos elementos en común.
