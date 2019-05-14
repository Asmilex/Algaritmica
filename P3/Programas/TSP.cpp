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

bool save_file (const string fichero, const vector<int> & resultados, const vector<double> & x, const vector<double> & y) {
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

int insercion (const vector<vector<int>> & map, vector<int> & resultados, int c0, int c1, int c2) {

    int n = map.size();
    int distancia = 0;

    resultados.clear();
    resultados.push_back(c0);
    resultados.push_back(c1);
    resultados.push_back(c2);

    distancia += map[c0-1][c1-1];
    distancia += map[c1-1][c2-1];
    distancia += map[c2-1][c0-1];

    //cout << c0 << "," << c1 << "," << c2 << endl;

    vector<int> candidatos;
    for(int i = 1; i<=n; i++)
        if(i!=c0 && i!=c1 && i!=c2)
            candidatos.push_back(i);

 /*   for(int i=0; i<resultados.size(); i++){
        cout << endl << ", " << resultados[i];
    }*/
    int nextCity, incrementoMin, incremento, posicion;

    while(candidatos.size()>0){

        nextCity=candidatos[0];
        incrementoMin = INT_MAX;


        for (int i = 0; i < candidatos.size(); i++){

            for(int j = 0; j < resultados.size(); j++){
                //Calcular incrementp total si insertamos el candidato i en la posición j

                //Restar la distancia entre el que está en la posición j y la j+1
                incremento = map[resultados[j]-1][candidatos[i]-1] +
                             map[candidatos[i]-1][resultados[(j+1)%resultados.size()]-1] -
                             map[resultados[j]-1][resultados[(j+1)%resultados.size()]-1];
                //Sumar las distancias que sumaria meter ahi el nodo

                if(incremento < incrementoMin){
                    incrementoMin  = incremento;
                    nextCity = candidatos[i];
                    posicion = j;
                }

            }
        }

        resultados.insert(resultados.begin()+posicion,nextCity);
        candidatos.erase(remove(candidatos.begin(),candidatos.end(),nextCity));
        distancia+=incrementoMin;

    }

    return distancia;
}

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
long int barrido (vector<T> x, vector<T> y, const vector<vector<int>> &matriz_adyacencia, vector<int> &orden) {
    /*
        Hacemos un barrido de abajo hacia arriba, buscando las ciudades por orden de altura.
        Si hay varias ciudades donde coinciden la misma altura, se barre desde izquierda a derecha
    */
    size_t n = y.size();

    orden.resize(n);

    T aux;
    size_t posicion;

    for (size_t i = 0; i < n; i++)
        orden[i] = i;

    // Reordenar con respecto a y. La primera ciudad se deja fija
    for (size_t i = 1; i < n; i++) {
        for (size_t j = 1; j < n; j++) {
            if (y[i] < y[j]) {
                // Mantener la posición entre los 3 vectores
                aux   = y[i];
                y[i]  = y[j];
                y[j]  = aux;

                aux   = x[i];
                x[i]  = x[j];
                x[j]  = aux;

                posicion = orden[i];
                orden[i] = orden[j];
                orden[j] = posicion;
            }
        }
    }

    // Reordenar x aquellos que tengan la misma posición y
    size_t saved_iter;
    for (size_t iter = 1; iter < n - 1; iter++) {
        // Encontrar repetidos
        saved_iter = iter;

        while (iter < n-1 && y[iter] == y[iter+1])
            iter++;

        //Ordenar parcialmente
        for (size_t i = saved_iter; i <= iter; i++) {
            for (size_t j = saved_iter; j <= iter; j++) {
                if (x[i] < x[j]) {
                    // Mantener la posición entre los 3 vectores
                    aux   = y[i];
                    y[i]  = y[j];
                    y[j]  = aux;

                    aux   = x[i];
                    x[i]  = x[j];
                    x[j]  = aux;

                    posicion = orden[i];
                    orden[i] = orden[j];
                    orden[j] = posicion;
                }
            }
        }
    }

    long int distancia_total = 0;

    for (int i = 1; i < n; i++) {
        distancia_total += matriz_adyacencia[i][i-1];
    }

    distancia_total += matriz_adyacencia[0][n-1];

    return distancia_total;
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
    vector<int> resultados;

    int dist;

    if (!parse_file (origen, x, y)) {
        cerr << "\nError en los valores\n";
        return 1;
    }

//
// ──────────────────────────────────────────── CALCULAR MATRIZ DE ADYACENCIA ─────
//

    vector<vector<int>> adyacencia (x.size(), vector<int>(x.size(), 0));

    for (int i=0; i<x.size(); i++)
        for (int j=0; j<y.size(); j++)
            adyacencia[i][j] = distancia(x[i], x[j], y[i], y[j]);

    //cout << "\nMATRIZ:\n";
    //print_matrix(adyacencia);

//
// ──────────────────────────────────────────────────────────────── ALGORITMO ─────
//

    if (algoritmo == "-i") {
        int c0=1,c1=1,c2=1;

        for(int i = 0; i<x.size(); i++){
            if(x[i]<x[c0-1]) c0=i+1;
            if(x[i]>x[c1-1]) c1=i+1;
            if(y[i]>y[c2-1]) c2=i+1;
        }


        dist = insercion(adyacencia, resultados, c0, c1, c2);
    }
    else if (algoritmo == "-c") {
        dist = cercania (adyacencia, resultados);
    }
    else if (algoritmo == "-b") {
        dist = barrido(x, y, adyacencia, resultados);
    }
    else {
        cerr << "Error en los parámetros.";
        return -1;
    }


    cout << "\nSuma de las distancias: " << dist;

    cout << "\nRecorrido: ";
    for (int i=0; i<resultados.size(); ++i)
        cout << resultados[i] + 1 << ", ";
    cout << endl;


//
// ────────────────────────────────────────────────────────── GUARDAR ARCHIVO ─────
//

    output = origen.append("_salida"); //cambiar sintaxis
    output = output.append(algoritmo);

    if (save_file(output, resultados, x, y))
        cout << "\nGuardado. Salida en: " << output << endl;
    else
        cerr << "\nError al guardar el fichero\n";

    return 0;
}
