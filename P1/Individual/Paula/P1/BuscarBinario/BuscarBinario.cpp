#include <chrono>
#include <random>
#include <iostream>
using namespace std;

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

int BuscarBinario (int *v, const int ini, const int fin, const int x){
  int centro;

  if (ini > fin)
    return -1;

  centro = (ini+fin)/2;

  if (v[centro] == x)
    return centro;

  if (v[centro] > x)
    return BuscarBinario(v, ini, centro-1, x);

  return BuscarBinario(v, centro+1, fin, x);
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cerr << "./programa tamaño";
        return -1;
    }

    int tamano = atoi(argv[1]);
    int * array = new int [tamano];

    heapsort(array, tamano);

    cout << tamano << "\t";

    auto t_antes = chrono::high_resolution_clock::now();
    int err = BuscarBinario(array, 0, tamano, -2);
    auto t_despues   = chrono::high_resolution_clock::now();
    unsigned long t_ejecucion = chrono::duration_cast<chrono::nanoseconds>(t_despues - t_antes).count();

    cout << t_ejecucion << endl;

    delete [] array;

    return 0;
}
