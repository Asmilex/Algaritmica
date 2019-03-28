#include <vector>
#include <iostream>
#include <random>

using namespace std;

int maximo(vector<int> &flechita, int l, int r){

    if(r-l==1){
        if(flechita[l]<flechita[r])
            return flechita[r];
        else
        {
            return flechita[l];
        }
        
    }

    if(r==l){
        return flechita[l];
    }

    else{
        int m=(l+r)/2;
        int maxL=maximo(flechita,l,m);
        int maxR=maximo(flechita,m+1,r);
        if(maxL<maxR)
            return maxR;
        else
            return maxL;
    }
}

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

    cout << "\nMAXIMO: " << maximo(flechita,0,flechita.size()-1);
}
