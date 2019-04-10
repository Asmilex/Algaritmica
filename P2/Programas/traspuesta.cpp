#include <vector>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

void generar_aleatorios (vector<vector<int>> &matriz, const size_t N, const size_t M) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-100,100);

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < M; ++j)
            matriz[i][j] = dist(rng);

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

void trasposicion_DyV (vector<vector<int>> & matriz) {
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
    if (argc != 4) {
        cerr << "./traspuesta filas columnas. Matriz de N \\cdot M {1,0}\nSi el último parámetro es 1, se ejecutará divide y vencerás";
        return -1;
    }

    // Parse parameters
    int N = atoi(argv[1]), M = atoi(argv[2]);
    int dim = max(N, M);
    bool is_DyV = atoi(argv[3]);

    vector<vector<int>> matriz     (dim, vector<int>(dim, -999));
    vector<vector<int>> traspuesta (dim, vector<int>(dim, -999));

    generar_aleatorios(matriz, N, M);

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    chrono::high_resolution_clock::time_point t_antes = chrono::high_resolution_clock::now();

    if (is_DyV) {
        trasposicion_DyV(matriz);
    }
    else {
        trasposicion_usual(matriz, traspuesta);
    }

    chrono::high_resolution_clock::time_point t_despues = chrono::high_resolution_clock::now();

    unsigned long t_ejecucion = chrono::duration_cast<std::chrono::nanoseconds>(t_despues - t_antes).count();

    cout << N*M << " " << t_ejecucion << endl;

    /* cout << "\nMatriz a trasponer:";
    print_matrix(matriz, N, M);

    trasponer(matriz);

    cout << "\nMatriz traspuesta:";
    print_matrix(matriz, M, N);

    vector<vector<int>> traspuesta (dim, vector<int>(dim, -999));

    cout << "\n\nTraspuesta lineal:";
    trasposicion_usual(matriz, traspuesta);

    print_matrix(traspuesta, N, M); */
}
