---
title: Práctica 4. Programación dinámica
revealOptions:
    transition: 'Fade'
    theme: robot-lung
    highlight-theme: github

---

# Práctica 3. Algoritmos voraces
Grupo: Las Algas

> Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

---

## Objetivos

- Encontrar la máxima subsecuencia de caracteres común que aparecen en ambas cadenas de izquierda a derecha.

---

## Método de la P.D.
- **Naturaleza N-etápica**.
- **Cumplimiento del POB**.
- **Ecuación de recurrencia**.
- **Encontrar la solución**.

---

## Código
```c++
cadena LCS ( cadena X, cadena Y, entero m, entero n) {
    si alguna cadena esta vacía:
        devolver cadenavacía
    si coincide el último carácter:
        devolver LCS (X,Y,m-1,n-1)
    si costos[m-1][n] >= costos[m][n-1]
        devolver LCS(X,Y,m-1;n)
    si no:
        devolver LCS(X,Y,m,n-1)
}
```

---

## Código
```c++
LCS_coste (cadena X, cadena Y, entero m, entero n) {
    para cada 0<=i<=m
        para cada 0<=j<=n
            si coincide el caracter:
                costos[i+1][j+1] = costos[i][j]+1
            si no:
                costos[i+1][j+1] = max(costos[i][j+1], costos[i+1][j])
}
```

---

## Ecuación recurrente



---

## Ejemplo

<img src="./Imagen/cosa-casa.jpg" width="400">

---

## Conclusiones
- Se progresa etapa por etapa con subproblemas que se diferencian entre si en una unidad en sus tamaños.
- Usamos PD porque los subproblemas comparten subproblemas.
- Se optiene la solución optimal.
- Gran uso de recursos (memoria).
