#include <algorithm>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int maximo(const vector<int> & flechita) {
    return * max_element(flechita.begin(), flechita.end());
}

int minimo(const vector<int> & flechita) {
    return * min_element(flechita.begin(), flechita.end());
}

int maximoDyV (const vector<int> &flechita, int l, int r) {
    if(l<=r) {
        if (r - l <= 1) {
            if (flechita[l] < flechita[r])
                return flechita[r];
            else
                return flechita[l];
        }
        else {
            int m    = (l + r)/2;
            int maxL = maximoDyV(flechita, l, m);
            int maxR = maximoDyV(flechita, m + 1, r);

            if (maxL < maxR)
                return maxR;
            else
                return maxL;
        }
    }
}

int minimoDyV (const vector<int> &flechita, int l, int r) {
    if (l<=r) {
        if (r - l <= 1) {
            if (flechita[l] > flechita[r])
                return flechita[r];
            else
                return flechita[l];
        }
        else {
            int m    = (l + r)/2;
            int minL = minimoDyV(flechita, l, m);
            int minR = minimoDyV(flechita, m + 1, r);

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
    if (argc != 3) {
        cerr << "Fallo en los parámetros";
        return -1;
    }

    int n = atoi(argv[1]);
    bool is_DyV = atoi(argv[2]);

    vector<int> flechita;

    generar_aleatorios(flechita, n);

    /*for (auto num: flechita)
        cout << num << ", ";*/

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    chrono::high_resolution_clock::time_point t_antes = chrono::high_resolution_clock::now();

    if (is_DyV) {
        int maximovector = maximoDyV(flechita, 0, flechita.size());
        int minimovector = minimoDyV(flechita, 0, flechita.size());
    }
    else {
        int maximovector = maximo(flechita);
        int minimovector = minimo(flechita);
    }

    chrono::high_resolution_clock::time_point t_despues = chrono::high_resolution_clock::now();
  	unsigned long t_ejecucion = chrono::duration_cast<std::chrono::nanoseconds>(t_despues - t_antes).count();
  	cout << "para tamanio: " << n << " tiempo de ejecucion: "<< t_ejecucion <<endl;
    //cout << "\nMáximo: " << maximo(flechita, 0, flechita.size() - 1) << "\n\n";
    //cout << "\nMínimo: " << minimo(flechita, 0, flechita.size() - 1) << "\n\n";
}
