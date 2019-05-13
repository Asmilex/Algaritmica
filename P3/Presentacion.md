---
title: Práctica 3. Algoritmos voraces
revealOptions:
    transition: 'Fade'
    theme: robot-lung

---

# Práctica 2. Divide y vencerás
Grupo: Las Algas

> Ana Buendía, Andrés Millán, Paula Villanueva, Juan Antonio Villegas

---

## Objetivos
- Aprender a aplicar algoritmos voraces.
- Resolver el problema del Viajante de Comercio.
- Diseñar un algoritmo que maximice el número de contenedores cargados en un barco.
- Diseñar un algoritmo que maximice el peso cargado en un barco.

---

## Especificaciones

| Persona      | CPU               | OS                    |
|--------------|-------------------|-----------------------|
| Ana          | i5-6200U 2.30GHz  | Ubuntu 16.04 LTS      |
| Andrés       | i5-8250U 3.40GHz  | Antergos 4-19.29 LTS  |
| Paula        | i7-5600U 2.60GHz  | Ubuntu 18.04 LTS      |
| Juan Antonio | i7-4500U 3.00GHz  | Ubuntu 18.04 LTS      |

---

## Problema del Viajante de Comercio

---

### Estructura
```c++
struct Contenedor {
    string id;
    int peso;

    Contenedor(string i, int p) {
        id   = i;
        peso = p;
    }
};
```

```c++
typedef set<Contenedor, lex_compare> mySet;
```

---

### Enfoque Greedy

Trataría de ir incluyendo los contenedores <u>menos</u> pesados hasta que no quepan más.
Los elementos que nos definen el enfoque Greedy son:

- Un **conjunto de candidatos**: En este caso son los contenedores disponibles.
- Un **conjunto de candidatos ya usados**: Que son los contenedores que se van incluyendo en el barco.
- Una **función solución** que nos dice cuando un subconjunto de candidatos forma una solución: Un conjunto de contenedores es solución (óptima o no) cuando el peso ya almacenado en el barco no pueda albergar el siguiente contenedor más pequeño.
- Un **criterio de factibilidad**: Un conjunto de contenedores es válido mientras que su peso total no exceda la carga máxima. Observar que todos los contenedores son factibles mientras no se encuentre uno que no lo sea, y una vez se encuentra, todos los demás no son factibles.
- Una **función de selección**: El siguiente candidato más prometedor es el siguiente contenedor menos pesado.
- Una **función objetivo**: El objetivo es maximizar el número de contenedores en el barco.

---

### Máximizar los contenedores cargados

```c++
int cargaMaxContenedores (vector<Contenedor> &barco, mySet &contenedores) {
    int pesoTotal = 0;

    for (auto i = contenedores.begin(); i != contenedores.end() && pesoTotal + (*i).peso <= K; ++i){
        barco.push_back(*i);
        pesoTotal += (*i).peso;
    }

    return pesoTotal;
}
```

---

#### Eficiencia teórica

$$T(n)=a+b\cdot n$$

El algoritmo es $O(n)$.

---

### Maximizar el peso cargado

```c++
int cargaMaxPeso (vector<Contenedor> &barco, mySet &contenedores) {
    int pesoTotal = 0;

    for (auto i = contenedores.rbegin(); i != contenedores.rend(); ++i) {
        if (pesoTotal + (*i).peso <= K) {
            barco.push_back(*i);
            pesoTotal += (*i).peso;
        }
    }

    return pesoTotal;
}
```

---

#### Eficiencia teórica

$$T(n)=a+b\cdot n$$

El algoritmo es $O(n)$.

---

### Eficiencia total

Tiempo del bucle:
$$\sum_{i=1}^n \log_2(i)$$
$$\sum_{i=1}^n \log_2(i)\leq \sum_{i=1}^n \log_2(n)=n\cdot \log_2(n)$$
Luego se tiene: $O(n\cdot \log_2(n))$.

---

### Optimalidad de maximizar los contenedores cargados

- Supongamos que $S=\{c_1,\dots,c_m\}$ es la solución que devuelve nuestro algoritmo y $P_S=\{p_1,\dots,p_m\}$ son los pesos asociados.
- Supongamos que $S'=\{c_1',\dots,c_k'\}$ es otra solución más óptima, es decir, $k>m$.
- Consideramos el "primer elemento que se quedó fuera de la solución del algoritmo", es decir, el contenedor menos pesado que no forma parte de $S$, lo denotamos como $c$ y a su peso como $p_c$.
- Se demuestra por reductio ad absurdum
- Tenemos que $T=\{c_1,\cdots,c_m,c'_{m+1},\cdots,c'_k\}$ es solución del problema.
- Por cómo hemos escogido $c$ tenemos $T'=\{c_1,\cdots,c_m,c\}$ es solución. Contradicción, si fuera solución nuestro algoritmo habría incluido $c$.
---

