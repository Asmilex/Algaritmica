#include <iostream>
#include <chrono>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

//
// ───────────────────────────────────────────────────────────────── ARCHIVOS ─────
//

template <class T>
bool parse_file (const string origen, vector<T> &xCords, vector<T> &yCords) {
    ifstream f(origen);
    bool return_value;

    if (!f) {
        cerr << "Fallo al abrir el fichero\n";
        return_value = false;
    }
    else {
        double n;
        string dimension;

        do {
            f >> dimension;
        } while (dimension != "DIMENSION:");

        f >> n;

        string coordenadas;

        do {
            f >> coordenadas;
        } while (coordenadas != "NODE_COORD_SECTION");

        xCords.clear();
        yCords.clear();

        int i, j;
        double temporal;

        for (j = 0; j < n; j++) {
            f >> i;
            f >> temporal;
            xCords.push_back(temporal);

            f >> temporal;
            yCords.push_back(temporal);
        }

        return_value = true;

        f.close();
    }

    return return_value;
}


template <class T>
bool save_file (const string fichero, const vector<T> & resultados, const vector<T> & xCords, const vector<double> & yCords) {
    ofstream f(fichero);

    if (!f) {
        cerr << "Fallo al abrir el archivo de salida";
        return false;
    }
    else {
        f << "DIMENSION: " << resultados.size() << endl;

        for (int i = 0; i < resultados.size(); i++)
            f << resultados[i] + 1 << " " << xCords[resultados[i]] << " " << yCords[resultados[i]] << endl;

        f << resultados[0]+1 << " " << xCords[resultados[0]] << " " << yCords[resultados[0]] << endl;

        f.close();

        return true;
    }
}

//
// ──────────────────────────────────────────────────────────────────── OTROS ─────
//

template <class T>
double distancia (const T x1, const T x2, const T y1, const T y2)  {
    return sqrt(  (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) );
}


template <class T>
void print_matrix (const vector<vector<T>> &matriz) {
    for (int i = 0; i < matriz.size(); ++i) {
        for (int j = 0; j < matriz.size(); ++j)
            cout << matriz[i][j] << "\t";

        cout << endl;
    }
}

//
// ─────────────────────────────────────────────────────────────── ALGORITMOS ─────
//

int insercion () {}

double cercania (const vector<vector<double>> &map, vector<double> &resultados) {
    int n = map.size();

    resultados.resize(n);
    resultados[0] = 0;

    double dmin, suma_distancias = 0, distancia = 0;
    vector<double> c(n-1);
    int i;

    for (i = 1; i<n; i++){
        c[i-1] = (double) i;
    }

    for (size_t k = 1; k < n; k++) {
        dmin = INT_MAX;

        for (size_t j = 0; j < n; j++) {
            if ( find(resultados.begin(), resultados.end(), j) == resultados.end() ) {
                distancia = map[ max(c[j], resultados[k-1] )][ min(c[j], resultados[k-1]) ];

                if (distancia < dmin) {
                    i = j;
                    dmin = distancia;
                }
            }

            suma_distancias += dmin;
            resultados[k] = i;
          }
    }

    suma_distancias += map[ max(resultados[0], resultados[n-1]) ][ min(resultados[0], resultados[n-1]) ];

    return suma_distancias;
    // Da error de compilación. Pero es que no sé cómo arreglarlo sin cambiarlo todo.
    // Está pensadopara enteros. Pero los datos están con decimales.
    // Fuck this shit
}

int TBD () {}

//
// ──────────────────────────────────────────────── I ──────────
//   :::::: M A I N : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────
//

int main(int argc, char const *argv[]) {
    /*
        Parámetros
            -i => ejecutar inserción
        1:  -c => ejecutar cercanía
            -n => ejecutar nuestra implementación

        Son exhaustivos

        2: nombre del archivo

    */

    if (argc != 3) {
        cerr << "Fallo de parámetros (mira el cpp)";
        return 1;
    }

    string algoritmo = argv[1];
    string origen    = argv[2];

    vector<double> xCords, yCords;
    parse_file(origen, xCords, yCords);

    vector<vector<double>> map (xCords.size(), vector<double>(xCords.size(), 0));
    double dist;

    for (int i = 0; i < xCords.size(); ++i) {
        for (int j = 0; j < yCords.size(); ++j) {
            dist = distancia(xCords[i], xCords[j], yCords[i], yCords[j]);
            map[i][j] = (dist);
        }
    }

    print_matrix(map);
    vector<double> resultados;

    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    chrono::high_resolution_clock::time_point t_antes, t_despues;


    if (algoritmo == "-i") {
        t_antes   = chrono::high_resolution_clock::now();
        insercion();
        t_despues = chrono::high_resolution_clock::now();
    }
    else if (algoritmo == "-c") {
        t_antes   = chrono::high_resolution_clock::now();
    //    cercania(map, resultados);
        t_despues = chrono::high_resolution_clock::now();
    }
    else if (algoritmo == "-n") {
        t_antes   = chrono::high_resolution_clock::now();
        TBD();
        t_despues = chrono::high_resolution_clock::now();
    }
    else
        cerr << "Cago en la hostia pon bien los parámetros";

    unsigned long t_ejecucion = chrono::duration_cast<std::chrono::nanoseconds>(t_despues - t_antes).count();


    return 0;
}
