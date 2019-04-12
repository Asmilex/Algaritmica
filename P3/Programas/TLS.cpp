#include <iostream>
#include <chrono>
#include <tslib.h>
#include <string>

using namespace std;

int insercion () {}
int cercania () {}
int TBD () {}


int main(int argc, char const *argv[])
{
    /*
        Parámetros:
        -i => ejecutar inserción
        -c => ejecutar cercanía
        -n => ejecutar nuestra implementación
    */

    if (argc != 2) {
        cerr << "Fallo de parámetros (mira el cpp)";
        return 1;
    }

    string algoritmo = argv[1];

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