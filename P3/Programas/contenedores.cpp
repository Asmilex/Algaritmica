#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <random>
#include <chrono>


using namespace std;

#define K 10000

struct Contenedor{ 
        string id;
        int peso;

        Contenedor(string i, int p){
            id=i;
            peso=p;
        }
};

struct lex_compare {
    bool operator() (const Contenedor& c1, const Contenedor& c2) const {
        return c1.peso < c2.peso;
    }
};

typedef set<Contenedor, lex_compare> mySet;

int cargaMaxPeso(vector<Contenedor> &barco, mySet &contenedores){
    int pesoTotal=0;
    for(auto i = contenedores.rbegin(); i!=contenedores.rend() && pesoTotal<K; ++i){
        if(pesoTotal+(*i).peso<=K){
            barco.push_back(*i);
            pesoTotal+=(*i).peso;
        }
    }
    return pesoTotal;
}

int cargaMaxContenedores(vector<Contenedor> &barco, mySet &contenedores){
    int pesoTotal=0;
    for(auto i = contenedores.begin(); i!=contenedores.end() && pesoTotal+(*i).peso<=K; ++i){
            barco.push_back(*i);
            pesoTotal+=(*i).peso;
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

void imprimeLosContenedores(const mySet &contenedores){
    for(auto i = contenedores.begin(); i!=contenedores.end(); ++i){
        cout << (*i).id << ": "<<(*i).peso << "Kg\t";
    }
    cout << endl;
}

void imprimeElBarco(vector<Contenedor> barco){
    for(auto i = barco.begin(); i!=barco.end(); ++i){
        cout << (*i).id << ": "<<(*i).peso << "Kg\t";
    }
    cout << endl;
}

int main(int argc, char ** argv){
    if(argc<2){
        cout << "Error en los parámetros" << endl;
        cout << "Sintaxis: "<< argv[0] << " <Numero de contenedores>" << endl;
        exit(-1);
    }
    int N=atoi(argv[1]);
    int pesoMax=1000;

    mySet contenedores;
    vector<Contenedor> barco;
    int pesoFinal;

    cout << "LA MMA DEL BARCO ES " << K << " Y LOS CONTENEDORES PESAN HASTA " << pesoMax << " Kg" << endl;

    generarContenedores(contenedores, N, pesoMax);
    cout << "\nCONTENEDORES DISPONIBLES:" << endl;
    imprimeLosContenedores(contenedores);

    pesoFinal=cargaMaxPeso(barco, contenedores);
    cout << "\nBARCO CARGADO CON: " << pesoFinal << "Kg (MÁXIMO PESO)" << endl;
    imprimeElBarco(barco);

    barco.clear();

    pesoFinal=cargaMaxContenedores(barco, contenedores);
    cout << "\nBARCO CARGADO CON: " << pesoFinal << "Kg (MÁXIMO NÚMERO DE CONTENEDORES)" << endl;
    imprimeElBarco(barco);




}


