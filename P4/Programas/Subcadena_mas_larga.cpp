#include <iostream>
#include <string>
using namespace std;

#define MAX 20

int costos[MAX][MAX];

string LCS (string X, string Y, int m, int n) {
	if (m == 0 || n == 0)
		return string("");

	if (X[m - 1] == Y[n - 1]) {
		return LCS(X, Y, m - 1, n - 1) + X[m - 1];
	}

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
	string X = "acbaed", Y = "abcadf";
	int m = X.length(), n = Y.length();

	LCS_coste(X, Y, m, n);

	cout << LCS(X, Y, m, n);

	return 0;
}