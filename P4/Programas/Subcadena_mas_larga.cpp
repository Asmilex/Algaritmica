#include <iostream>
#include <string>
#include <random>
using namespace std;

#define MAX 10

int costos[MAX][MAX];

std::string random_string(std::string::size_type length)
{
    static auto& chrs = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while(length--)
        s += chrs[pick(rg)];

    return s;
}

void print_matrix (int matriz[][MAX]) {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j)
            cout << matriz[i][j] << "\t";

        cout << endl;
    }
}

string LCS (string X, string Y, int m, int n) {
	if (m == 0 || n == 0)
		return string("");

	if (X[m - 1] == Y[n - 1])
		return LCS(X, Y, m - 1, n - 1) + X[m - 1];


	if (costos[m - 1][n] > costos[m][n - 1])
		return LCS(X, Y, m - 1, n);
	else
		return LCS(X, Y, m, n - 1);
}

void LCS_coste (string X, string Y, int m, int n) {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X[i - 1] == Y[j - 1])
				costos[i][j] = costos[i - 1][j - 1] + 1;
			else
				costos[i][j] = max(costos[i - 1][j], costos[i][j - 1]);
		}
	}
}

int main (int argc, char const *argv[]) {
	string X = random_string(MAX), Y = random_string(MAX);

	int m = X.length(), n = Y.length();

	LCS_coste(X, Y, m, n);

	cout << "Palabras:\n\t" << X << "\n\t" << Y << endl;
	cout << "Subsecuencia más larga:\n\t" << LCS(X, Y, m, n) << endl << endl;

	print_matrix(costos);

	return 0;
}