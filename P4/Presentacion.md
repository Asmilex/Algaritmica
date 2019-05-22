---
title: Práctica 4. Programación dinámica
revealOptions:
    transition: 'Fade'
    theme: robot-lung
    highlight-theme: github

---

# Práctica 4. Programación dinámica
Grupo: Las Algas

> Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

---

## Objetivos

- Comprender el enfoque de la programación dinámica
- Identificar los elementos característicos en un problema concreto.
- Calcular la subsecuencia de caracteres común más larga dadas dos cadenas.
- Resolver dicho problema aplicando este método de programación

---

## Subsecuencia de caracteres más larga

### Enunciado

- Sean dos secuencias de caracteres $X= (x_1, x_2, \dots , x_m)$ e $Y= (y_1, y_2, \dots , y_n)$.
- Encontrar la máxima subsecuencia de caracteres común de izquierda a derecha (no necesariamente de forma contigua).

---

## Método de la P.D.
- **Naturaleza N-etápica**.
- **Cumplimiento del POB**.
- **Ecuación de recurrencia**.
- **Encontrar la solución**.

---

### Ecuación recurrente
Sean $X[0..n]$ e $Y[0..m]$, entonces

- Si $X[n-1]=Y[m-1]$:

      LCS(X[0..n],Y[0..m])=
      =LCS(X[0..n-1],Y[0..m-1])+
       +X[m-1]

- En otro caso:

      LCS(X[0..n],Y[0..m])=
      =max(LCS(X[0..n-1],Y[0..m]),
           LCS(X[0..n],Y[0..m-1]))
---

### Código I
```c++
cadena LCS (cadena X, cadena Y, entero m, entero n) {
    si alguna cadena está vacía:
        devolver cadenavacía
    si coincide el último carácter:
        devolver LCS(X,Y,m-1,n-1) + último carácter
    si costos[m-1][n] >= costos[m][n-1]
        devolver LCS(X,Y,m-1;n)
    si no:
        devolver LCS(X,Y,m,n-1)
}
```

---

### Código II
```c++
LCS_coste (cadena X, cadena Y, entero m, entero n) {
    para cada 0<=i<m
        para cada 0<=j<n
            si coincide el carácter:
                costos[i+1][j+1] = costos[i][j]+1
            si no:
                costos[i+1][j+1] = max(costos[i][j+1],
                                       costos[i+1][j])
}
```

---

### Ejemplo I

<img src="./Imagen/cosa-casa.jpg" width="400">

---

### Ejemplo II

<img src="./Imagen/CasaCosaEjecucion.png" width="750">

---

### Ejemplo III

<img src="./Imagen/EjemploGrande.png" width="1400">

---

### Conclusiones I

- En este problema la P.D. tiene cosas en común con DyV.
- Usamos PD porque los subproblemas comparten subproblemas.
- Se optiene la solución optimal.
- Gran uso de recursos (memoria).

---

### Conclusiones II

- La matriz de costos nos ahorra operaciones repetidas.
- Se progresa etapa por etapa con subproblemas que se diferencian entre si en una unidad en sus tamaños.
- La recurrencia puede ser compleja si el tamaño de las cadenas es grande y tienen pocos elementos en común.
