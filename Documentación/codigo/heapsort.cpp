#include <chrono>
#include <random>
#include <iostream>
using namespace std;

//
// ─── BURBUJA ────────────────────────────────────────────────────────────────────
//

    void burbuja (int T[], int inicial, int final) {
        int i, j, aux;

        for (i = inicial; i < final - 1; i++) {
            for (j = final - 1; j > i; j--) {
                if (T[j] < T[j-1]) {
                    aux = T[j];
                    T[j] = T[j-1];
                    T[j-1] = aux;
                }
            }
        }
    }

//
// ─── ALGORITMO 1 ────────────────────────────────────────────────────────────────
//

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

//
// ─── ALGORITMO 4 ────────────────────────────────────────────────────────────────
//

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

//
// ─── ALGORITMO 5 ────────────────────────────────────────────────────────────────
//

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

void menea_el_vector(int * array, int tamano) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,1000);

    for (int i = 0; i < tamano; i++)
        array[i] = dist(rng);
}



int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cerr << "./programa tamaño";
        return -1;
    }

    int tamano = atoi(argv[1]);
    int * array = new int [tamano];

    menea_el_vector(array, tamano);

    //cout << tamano << "   ";

/*
    auto t_antes = chrono::high_resolution_clock::now();
    pivotar(array, 0, tamano);
    auto t_despues = chrono::high_resolution_clock::now();
    unsigned long t_ejecucion = chrono::duration_cast<chrono::microseconds>(t_despues - t_antes).count();

    cout << "Pivotaje: " << t_ejecucion << endl;
*/

    auto t_antes = chrono::high_resolution_clock::now();
    heapsort(array, tamano);
    auto t_despues   = chrono::high_resolution_clock::now();
    unsigned long t_ejecucion = chrono::duration_cast<chrono::microseconds>(t_despues - t_antes).count();

    cout <<tamano << " " << t_ejecucion << endl;
/*
    menea_el_vector(array, tamano);
    t_antes = chrono::high_resolution_clock::now();
    burbuja(array, 0, tamano);
    t_despues   = chrono::high_resolution_clock::now();
    t_ejecucion = chrono::duration_cast<chrono::microseconds>(t_despues - t_antes).count();

    cout << t_ejecucion << endl;
*/
    /* t_antes = chrono::high_resolution_clock::now();
    int err = Busqueda(array, tamano, array[tamano - tamano/16 - 1]);
    t_despues   = chrono::high_resolution_clock::now();
    t_ejecucion = chrono::duration_cast<chrono::microseconds>(t_despues - t_antes).count();

    cout << "Búsqueda: " << t_ejecucion << " -- " << err << endl;

    t_antes = chrono::high_resolution_clock::now();
    err = BuscarBinario(array, 0, tamano, array[tamano - tamano/2]);
    t_despues   = chrono::high_resolution_clock::now();
    t_ejecucion = chrono::duration_cast<chrono::microseconds>(t_despues - t_antes).count();

    cout << "Buscar binario: " << t_ejecucion << " -- " << err << endl;

    t_antes = chrono::high_resolution_clock::now();
    EliminaRepetidos(array, tamano);
    t_despues   = chrono::high_resolution_clock::now();
    t_ejecucion = chrono::duration_cast<chrono::microseconds>(t_despues - t_antes).count();

    cout << "Elimina repetidos: " << t_ejecucion << endl << endl; */

    delete [] array;

    return 0;
}
