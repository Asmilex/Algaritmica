#include <iostream>
#include <chrono>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

bool parse_file (const string origen, vector<double> &xCords, vector<double> &yCords) {
    ifstream f(origen);
    bool return_value;

    if (!f) {
        cerr << "Fallo al abrir el fichero\n";
        return_value = false;
    }
    else {
        double n;
        string dimension;

        f >> dimension;
        f >> n;

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
    }

    return return_value;
}

double distancia (double x1, double y1, double x2, double y2)  {
    return sqrt(  (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) );
}

template <class T>
void print_matrix(const vector<vector<T>> &matriz) {
    for (int i = 0; i < matriz[i].size(); ++i) {
        for (int j = 0; j < matriz.size(); ++j)
            cout << matriz[i][j] << "\t";

        cout << endl;
    }
}

int insercion () {}
int cercania () {}
int TBD () {}

int main(int argc, char const *argv[])
{
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

    vector<vector<double>> map(xCords.size());
    double dist;

    for (size_t i = 0; i < xCords.size(); ++i) {
        for (size_t j = 0; j < yCords.size(); ++j) {
            dist = distancia(xCords[i], xCords[j], yCords[i], yCords[j]);   //FIXME problemas
            map[i].push_back(dist);
        }
    }

    //print_matrix(map); //FIXME

    if (algoritmo == "-i")
        insercion();
    else if (algoritmo == "-c")
        cercania();
    else if (algoritmo == "-n")
        TBD();
    else
        cerr << "Cago en la hostia pon bien los parámetros";

    return 0;
}