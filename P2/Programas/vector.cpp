#include <vector>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int maximo (vector<int> &flechita, int l, int r) {

    if(l<=r){
        if (r - l <= 1) {
            if (flechita[l] < flechita[r])
                return flechita[r];
            else
                return flechita[l];
        }
        else {
            int m    = (l + r)/2;
            int maxL = maximo(flechita, l, m);
            int maxR = maximo(flechita, m + 1, r);

            if (maxL < maxR)
                return maxR;
            else
                return maxL;
        }        
    }

}

int minimo (vector<int> &flechita, int l, int r) {

    if(l<=r){
        if (r - l <= 1) {
            if (flechita[l] > flechita[r])
                return flechita[r];
            else
                return flechita[l];
        }

        else {
            int m    = (l + r)/2;
            int minL = minimo(flechita, l, m);
            int minR = minimo(flechita, m + 1, r);

            if (minL < minR)
                return minL;
            else
                return minR;
        }
    }
}

void generar_aleatorios (vector<int> &flechita, const size_t tamano) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-10000,10000);

    for (size_t i = 0; i < tamano; ++i)
        flechita.push_back(dist(rng));
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cerr << "Fallo en los parámetros";
        return -1;
    }
     chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms

    vector<int> flechita;

    generar_aleatorios(flechita, atoi(argv[1]));

    t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
    maximo(flechita, 0, flechita.size() - 1);
    minimo(flechita, 0, flechita.size() - 1);
	tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

    tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

    cout << flechita.size() << " " << tejecucion << endl;

/*
    for (auto num: flechita)
        cout << num << ", ";

    cout << "\nMáximo: " << maximo(flechita, 0, flechita.size() - 1) << "\n\n";
    cout << "\nMínimo: " << minimo(flechita, 0, flechita.size() - 1) << "\n\n";
*/
}
