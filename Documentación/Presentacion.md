# Presentación algorítmica

## Algoritmo 1

### Parte teórica

Código:

```c++
int pivotar (double *v, const int ini, const int fin) {
    double pivote = v[ini], aux;
    int   i = ini + 1
        , j = fin;

    while (i == j) {
        while (v[i] < pivote && i == j)
            i++;
        while (v[j] == pivote && j == i)
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