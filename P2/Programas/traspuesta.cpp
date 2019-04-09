#include <vector>
#include <iostream>
#include <random>

using namespace std;

void generar_aleatorios (vector<vector<int>> &peaso_matriz, const size_t N, const size_t M) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-100,100);

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            peaso_matriz[i][j] = dist(rng);

    // Valor no válido para los elementos no admisibles
}

void intercambiar(vector<vector<int>> & matriz, int fIniA, int cIniA, int fIniB, int cIniB, int dim) {
    for (size_t i = 0; i < dim ; i++) {
        for (size_t j = 0; j < dim; j++) {
            int aux = matriz[fIniA + i][cIniA + j];
            matriz[fIniA + i][cIniA + j] = matriz[fIniB + i][cIniB + j];
            matriz[fIniB + i][cIniB + j] = aux;
        }
    }
}

void trasponerDyV (vector<vector<int>> & matriz, int fInicio, int fFin, int cInicio, int cFin) {
    if (fInicio < fFin) {
        int fMedio = (fInicio + fFin)/2;
        int cMedio = (cInicio + cFin)/2;

        trasponerDyV(matriz, fInicio,    fMedio, cInicio,    cMedio);
        trasponerDyV(matriz, fInicio,    fMedio, cMedio + 1, cFin);
        trasponerDyV(matriz, fMedio + 1, fFin,   cInicio,    cMedio);
        trasponerDyV(matriz, fMedio + 1, fFin,   cMedio + 1, cFin);

        intercambiar(matriz, fMedio + 1, cInicio, fInicio, cMedio + 1, fFin - fMedio);
    }
}

void trasponer (vector<vector<int>> & matriz) {
    trasponerDyV (matriz, 0, matriz[0].size()-1, 0, matriz.size()-1);
}

void trasposicion_usual (vector<vector<int>> matriz, vector<vector<int>> & destino) {
    for (int i = 0; i < matriz[0].size(); ++i)
        for (int j = 0; j < matriz.size(); ++j)
            destino[j][i] = matriz[i][j];
}

void print_matrix (vector<vector<int>> matrix, size_t N, size_t M) {
    printf("\n");

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j)
            cout << matrix[i][j] << "\t";

        cout << "\n";
    }

    printf("\n");
}

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        cerr << "./traspuesta filas columnas. Matriz de N \\cdot M";
        return -1;
    }

    int N = atoi(argv[1]), M = atoi(argv[2]);
    int dim = max(N, M);

    vector<vector<int>> matriz (dim, vector<int>(dim, -999));

    generar_aleatorios(matriz, N, M);

    cout << "\nMatriz a trasponer:";
    print_matrix(matriz, N, M);

    trasponer(matriz);

    cout << "\nMatriz traspuesta:";
    print_matrix(matriz, M, N);

    vector<vector<int>> traspuesta (dim, vector<int>(dim, -999));

    cout << "\n\nTraspuesta lineal:";
    trasposicion_usual(matriz, traspuesta);

    print_matrix(traspuesta, N, M);
}
