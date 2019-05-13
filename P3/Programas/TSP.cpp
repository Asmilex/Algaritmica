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

      x.clear();
      y.clear();

      int i, j;
      double temporal;

      for (j = 0; j < n; j++) {
          f >> i;
          f >> temporal;
          x.push_back(temporal);

          f >> temporal;
          y.push_back(temporal);
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
        f << "TOUR_SECTION" << endl;

        for (int i=0; i<resultados.size(); i++)
            f << resultados[i] + 1 << " " << x[resultados[i]] << " " << y[resultados[i]] << endl;

        f << resultados[0] + 1 << " " << x[resultados[0]] << " " << y[resultados[0]] << endl;

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

void print_matrix (const vector<vector<int>> & matriz) {
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

int cercania (const vector<vector<int>> & adyacencia, vector<int> & resultados) {
    int n = adyacencia.size();
    int dist_min, dist = 0, i, j, aux;
    long suma_distancias = 0;

    resultados.resize(n);
    resultados[0] = 0;

    for (i=1; i<n; i++) {
        dist_min = INT_MAX;

        for (j=0; j<n; j++)
            if (find(resultados.begin(), resultados.end(), j) == resultados.end()) {
                dist = adyacencia[max(j, resultados[i-1])][min(j, resultados[i-1])];

                if (dist < dist_min) {
                    aux = j;
                    dist_min = dist;
                }
            }

        suma_distancias += dist_min;
        resultados[i] = aux;
    }

    suma_distancias += adyacencia[max(resultados[0], resultados[n-1])][min(resultados[0], resultados[n-1])];

    return suma_distancias;
}

template <class T>
int barrido (vector<T> x, vector<T> y, vector<vector<double>> matriz_adyacencia, vector<int> resultados) {
    /*
        Hacemos un barrido de abajo hacia arriba, buscando las ciudades por orden de altura.
        Si hay varias ciudades donde coinciden la misma altura, se barre desde izquierda a derecha
    */
    size_t n = y.size();

    vector<size_t> orden (n);

    T aux;
    size_t posicion;

    for (size_t i = 0; i < n; i++)
        orden[i] = i + 1;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (y[i] < y[j]) {
                // Mantener la posición entre los 3 vectores
                y[i] = aux;
                y[i] = y[j];
                y[j] = aux;

                x[i] = aux;
                x[i] = y[j];
                x[j] = aux;

                orden[i] = posicion;
                orden[i] = orden[j];
                orden[j] = posicion;
            }
        }
    }

    // TODO
}

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

    string algoritmo = argv[1], origen = argv[2], output;
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

    vector<vector<int>> adyacencia (x.size(), vector<int>(x.size(), 0));

    for (int i=0; i<x.size(); i++)
        for (int j=0; j<y.size(); j++)
            adyacencia[i][j] = distancia(x[i], x[j], y[i], y[j]);

    //cout << "\nMATRIZ:\n";
    //print_matrix(adyacencia);

    if (algoritmo == "-i") {
        t_antes = chrono::high_resolution_clock::now();
        insercion();
        t_despues = chrono::high_resolution_clock::now();
    }
    else if (algoritmo == "-c") {
        t_antes = chrono::high_resolution_clock::now();
        cerc = cercania (adyacencia, resultados);
        t_despues = chrono::high_resolution_clock::now();

        cout << "\n" << cerc << "\n\n";
        cout << "\n";
    }
    else if (algoritmo == "-n") {
        t_antes = chrono::high_resolution_clock::now();
        TBD();
        t_despues = chrono::high_resolution_clock::now();
    }
    else {
        cerr << "Error en los parámetros.";
        return -1;
    }

    cout << "Recorrido: ";

    for (int i=0; i<resultados.size(); ++i) //resultados o x?
        cout << resultados[i] + 1 << ", ";

    t_ejecucion = chrono::duration_cast<std::chrono::nanoseconds>(t_despues - t_antes).count();
/*
    output = origen.append("_output"); //cambiar sintaxis

    if (save_file(output, resultados, x, y))
        cout << "\nGuardado. Salida en: " << output << endl;
    else
        cerr << "\nError al guardar el fichero\n";
*/
    return 0;
}
