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

bool parse_file (const string origen, vector<double> & x, vector<double> & y) {
    ifstream f(origen);
    bool return_value;

    if (!f) {
        cerr << "Fallo al abrir el fichero\n";
        return_value = false;
    }
    else {
        int n, i, j, aux;
        string dim;

        f >> dim;
        f >> n;

        x.clear();
        y.clear();

        for (i=0; i<n; j++) {
            f >> aux;
            f >> x[i];
            f >> y[i];
        }

        return_value = true;

        f.close();
    }

    return return_value;
}

bool load_file (const string fichero, const vector<int> & resultados, const vector<double> & x, const vector<double> & y) {
    ofstream f(fichero);

    if (!f) {
        cerr << "Fallo al abrir el archivo de salida";
        return false;
    }
    else {
        f << "DIMENSION: " << resultados.size() << endl;

        for (int i=0; i<resultados.size(); i++)
            f << resultados[i] + 1 << " " << x[resultados[i]] << " " << y[resultados[i]] << endl;

        f << resultados[0]+1 << " " << x[resultados[0]] << " " << y[resultados[0]] << endl;

        f.close();

        return true;
    }
}

//
// ──────────────────────────────────────────────────────────────────── OTROS ─────
//

int distancia (double x1, double x2, double y1, double y2)  {
    return ((int) rint(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2))));
}

void print_matrix (const vector<vector<int>> &matriz) {
    for (int i=0; i<matriz.size(); ++i) {
        for (int j=0; j<matriz.size(); ++j)
            cout << matriz[i][j] << "\t";

        cout << endl;
    }
}

//
// ─────────────────────────────────────────────────────────────── ALGORITMOS ─────
//

int insercion () {}

int cercania (const vector<vector<int>> & map, vector<int> & resultados) {
    int n = map.size();

    resultados.resize(n);
    resultados[0] = 0;

    double dmin, suma_distancias = 0, dist = 0;
    vector<int> c(n-1);
    int i;

    for (i=1; i<n; i++){
        c[i-1] = i;
    }

    for (size_t k=1; k<n; k++) {
        dmin = INT_MAX;

        for (size_t j=0; j<n; j++) {
            if (find(resultados.begin(), resultados.end(), j) == resultados.end() ) {
                dist = map[ max(c[j], resultados[k-1] )][ min(c[j], resultados[k-1]) ];

                if (dist < dmin) {
                    i = j;
                    dmin = dist;
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
        cerr << "\nFallo de parámetros (mira el cpp)\n";
        return 1;
    }

    string algoritmo = argv[1], origen = argv[2];
    vector<double> x, y;
    int dist, cerc;
    vector<int> resultados;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    chrono::high_resolution_clock::time_point t_antes, t_despues;
    unsigned long t_ejecucion;

    if (!parse_file (origen, x, y)){
      cerr << "\nError en los valores\n";
      return 1;
    }

    vector<vector<int>> map (x.size(), vector<int>(x.size(), 0));

    for (int i=0; i<x.size(); ++i)
        for (int j=0; j<y.size(); ++j)
            map[i][j] = distancia(x[i], x[j], y[i], y[j]);

    print_matrix(map);

    if (algoritmo == "-i") {
        t_antes = chrono::high_resolution_clock::now();
        insercion();
        t_despues = chrono::high_resolution_clock::now();
    }
    else if (algoritmo == "-c") {
        t_antes = chrono::high_resolution_clock::now();
        cerc = cercania (map, resultados);
        t_despues = chrono::high_resolution_clock::now();

        cout << "\n" << cerc << "\n\n";

        for (int i=0; i<resultados.size(); ++i)
            cout << resultados[i] << "\t";

        cout << "\n";
    }
    else if (algoritmo == "-n") {
        t_antes = chrono::high_resolution_clock::now();
        TBD();
        t_despues = chrono::high_resolution_clock::now();
    }
    else
        cerr << "Error en los parámetros.";

    t_ejecucion = chrono::duration_cast<std::chrono::nanoseconds>(t_despues - t_antes).count();

    return 0;
}
