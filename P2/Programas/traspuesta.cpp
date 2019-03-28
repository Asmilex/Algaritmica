#include <vector>
#include <iostream>
#include <random>

using namespace std;

void generar_aleatorios (vector<vector<int>> &peaso_matriz, const size_t N, const size_t M) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-10000,10000);

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            peaso_matriz[i][j] = dist(rng);

}

int main(int argc, char const *argv[])
{
    if (argc != 4) {
        cerr << "./traspuesta filas columnas tamaño. Matriz de N \\cdot M";
        return -1;
    }

    int N = atoi(argv[1]), M = atoi(argv[2]);

    vector<vector<int>> matriz (N, vector<int>(M));

    generar_aleatorios(matriz, N, M);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j)
            cout << matriz[i][j] << "\t";

        cout << "\n";
    }
}
