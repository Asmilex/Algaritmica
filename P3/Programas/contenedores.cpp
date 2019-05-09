#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

#define K 10000

struct Contenedor {
    string id;
    int peso;

    Contenedor(string i, int p) {
        id   = i;
        peso = p;
    }
};

struct lex_compare {
    bool operator() (const Contenedor& c1, const Contenedor& c2) const {
        return c1.peso < c2.peso;
    }
};

typedef set<Contenedor, lex_compare> mySet;

int cargaMaxPeso (vector<Contenedor> &barco, mySet &contenedores) {
    int pesoTotal = 0;

    for (auto i = contenedores.rbegin(); i != contenedores.rend(); ++i) {
        if (pesoTotal + (*i).peso <= K) {
            barco.push_back(*i);
            pesoTotal += (*i).peso;
        }
    }

    return pesoTotal;
}

int cargaMaxContenedores (vector<Contenedor> &barco, mySet &contenedores) {
    int pesoTotal = 0;

    for (auto i = contenedores.begin(); i != contenedores.end() && pesoTotal + (*i).peso <= K; ++i){
        barco.push_back(*i);
        pesoTotal += (*i).peso;
    }

    return pesoTotal;
}


void generarContenedores (mySet &contenedores, const size_t tamano, const int max) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,max);

    for (size_t i = 0; i < tamano; ++i){
        contenedores.insert(Contenedor("c"+to_string(i),dist(rng))) ;
    }

}

void imprimirContenedores(const mySet &contenedores) {
    for (auto contenedor: contenedores){
        cout << "\t" << contenedor.id << ": "<<contenedor.peso << "Kg\t";
    }

    cout << endl;
}

void imprimirBarco (vector<Contenedor> barco){
    for (auto elemento: barco){
        cout << "\t" << elemento.id << ": "<< elemento.peso << "Kg\t";
    }
    cout << endl;
}

int main(int argc, char ** argv){
    if (argc < 3) {
        cout << "Error en los parámetros" << endl;
        cout << "Sintaxis: "<< argv[0] << " <Numero de contenedores> <Modo benchmark {0,1}>" << endl;
        exit(-1);
    }

    int N       = atoi(argv[1])
      , pesoMax = 1000;
    bool benchmark = atoi(argv[2]);

    mySet contenedores;
    vector<Contenedor> barco;
    int pesoFinal;

    if (benchmark) {
        //cout << "MMA: " << K << "\tmax_weight: " << pesoMax << " KG" << endl;
        generarContenedores(contenedores, N, pesoMax);

        //pesoFinal = cargaMaxPeso(barco, contenedores);
        pesoFinal = cargaMaxContenedores(barco, contenedores);

        cout << N << " " << pesoFinal << " " << barco.size() <<  endl;
    }
    else {
        cout << "La MMA del barco es " << K << " y los contenedores pueden llegar a pesar hasta " << pesoMax << " KG" << endl;

        generarContenedores(contenedores, N, pesoMax);
        cout << "\nContenedores disponibles:" << endl;
        imprimirContenedores(contenedores);

        pesoFinal = cargaMaxPeso(barco, contenedores);
        cout << "\nBarco cargado con: " << pesoFinal << "KG (peso máximo)" << endl;
        imprimirBarco(barco);

        barco.clear();

        pesoFinal = cargaMaxContenedores(barco, contenedores);
        cout << "\nBarco cargado con: " << pesoFinal << "KG (máximo numero de contenedores)" << endl;
        imprimirBarco(barco);
    }
    return 0;
}