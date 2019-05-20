# Práctica 4: Programación dinámica

> Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

## Objetivos

* Comprender el enfoque de la programación dinámica.
* Identificar los elementos de la PD en un problema concreto
* Resolver dicho problema aplicando PD.

## Subsecuencia de caracteres más larga

(Poner enunciado aquí).

### Solución

La solución que proponemos se basa en examinar el último carácter de ambas cadenas, si coincide lo añadimos a la solución, si no, lo descartamos y buscamos una cadena común. Por ejemplo, sean X="casa" e Y="cosa". Tenemos:

$LCS("casa", "cosa")= LCS("cas","cos")+a$, ya que ambas comparten la última letra, calculamos ahora:

$LCS("cas","cos")=LSC("ca","co")+s$, de nuevo porque comparten la última letra, a continuación:

$LCS("ca","co")=max(LCS("c","co"), LCS("ca","c"))$, ya que esta vez no comparten la última letra.

$LCS("c","co")=max(LCS(" ","co"), LCS("c","c"))="c"$

$LCS("ca","c")=max(LCS("c","c"), LCS("ca"," "))="c"$

Recomponiendo las sucesivas recursiones obtenemos que el resultado es "$csa$".

Por tanto, la recurrencia que define nuestro algoritmo si tenemos $X[0..n]$ e $Y[0..m]$ es:

> $LCS(X[0..n],Y[0..m])=LCS(X[0..n-1],Y[0..m-1])+X[m-1]$     si     $X[n-1]=Y[m-1]$
>
> $LCS(X[0..n],Y[0..m])=max(LCS(X[0..n-1],Y[0..m]),LCS(X[0..n],Y[0..m-1]))$   en otro caso

Para agilizar los cálculos, hemos tratado con una matriz de costos $M$ que contiene la longitud de la mayor subsecuencia común entre los prefijos de $X$ e $Y$. El elemento $m_{ij}$ representa la longitud de la subsecuencia común más larga de $X[0..i-1]$ e $Y[0..j-1]$. 

En el ejemplo de $X="casa"$ e $Y="cosa"$ tenemos la matriz:

$A=\begin{pmatrix}\mathbf{1} & 1 & 1 & 1 \\ 1 & 1 & 1 & \mathbf{2} \\ 1 & 1 & \mathbf{2} & 2 \\ 1 & 1 & 2 & \mathbf{3} \end{pmatrix}$

Señalamos en negrita las entradas en las que $X[i-1]=Y[j-1]$. Para proceder, comenzamos a recorrer la matriz por la esquina inferior derecha. Si $X[i-1]=Y[j-1]$, se añade a la solución este carácter, y si no lo son, nos movemos hacia arriba o hacia la izquierda, dependiendo de qué celda sea mayor.





