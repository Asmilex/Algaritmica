#include <vector>
#include <iostream>
#include <random>

using namespace std;

void generar_aleatorios (vector<vector<int>> &peaso_matriz, const size_t tamano) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-10000,10000);

    for (size_t i = 0; i < tamano; ++i)
        for (size_t j = 0; j < tamano; ++j)
            peaso_matriz[i][j] = dist(rng);

}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cerr << "Fallo en los parámetros";
        return -1;
    }

    int tamano = atoi(argv[1]);

    vector<vector<int>> matriz (tamano, vector<int>(tamano));

    generar_aleatorios(matriz, tamano);

    for (size_t i = 0; i < tamano; ++i) {
        for (size_t j = 0; j < tamano; ++j)
            cout << matriz[i][j] << "\t";

        cout << "\n";
    }
}
