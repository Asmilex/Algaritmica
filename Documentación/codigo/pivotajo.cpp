#include <iostream>
using namespace std;

//
// ─── ALGORITMO 1 ────────────────────────────────────────────────────────────────
//

    int pivotar (double *v, const int ini, const int fin) {
        double pivote = v[ini], aux;
        int   i = ini + 1
            , j = fin;

        while (i <= j) {
            while (v[i] < pivote && i <= j)
                i++;

            while (v[j] <= pivote && j >= i)
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

//
// ─── ALGORITMO 2 ────────────────────────────────────────────────────────────────
//

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

//
// ─── ALGORITMO 3 ────────────────────────────────────────────────────────────────
//

    void EliminaRepetidos (double original[], int & nOriginal) {
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

//
// ─── ALGORITMO 4 ────────────────────────────────────────────────────────────────
//

    int BuscarBinario (double *v, const int ini, const int fin, const double x) {
        int centro;

        if (ini > fin)
            return 1;

        centro = (ini + fin)/2;

        if (v[centro] == x)
            return centro;

        if (v[centro] > x)
            return BuscarBinario(v, ini, centro-1, x);

        return BuscarBinario (v, centro+1, fin, x);
    }

//
// ─── ALGORITMO 5 ────────────────────────────────────────────────────────────────
//

    void heapsort (int T[], int num_elem) {
        int i;

        for (i = num_elem/2; i >= 0; i--)
            reajustar(T, num_elem, i);

        for (i = num_elem - 1; i >= 1; i--) {
            int aux = T[0];

            T[0] = T[i];
            T[i] = aux;
            reajustar(T, i, 0);
        }
    }

    void reajustar (int T[], int num_elem, int k) {
        int j, v;
        bool esAPO = false;

        v = T[k];

        while ( (k < num_elem/2) && !esAPO ) {
            j = k + k + 1;

            if ( j < (num_elem - 1) && T[j] < T[j+1] )
                j++;

            if (v >= T[j])
                esAPO = true;

            T[k] = T[j];
            k = j;
        }

        T[k] = v;
    }