#include <vector>
#include <iostream>
#include <random>

using namespace std;

void generar_aleatorios (vector<int> &flechita, const size_t tamano) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-10000,10000);

    for (size_t i = 0; i < tamano; ++i)
        flechita.push_back(dist(rng));
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cerr << "Fallo en los parámetros";
        return -1;
    }

    vector<int> flechita;

    generar_aleatorios(flechita, atoi(argv[1]));

    for (auto num: flechita)
        cout << num << ", ";
}
