

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

int** makeMatrix(int r, int c) {
    int** a = new int* [r];
    for (int i = 0; i < r; i++) a[i] = new int[c];
    return a;
}

void freeMatrix(int** a, int r) {
    for (int i = 0; i < r; i++) delete[] a[i];
    delete[] a;
}

void fill(int** a, int r, int c, int p = 0) {
    if (p == r * c) return;
    a[p / c][p % c] = -42 + rand() % 94;
    fill(a, r, c, p + 1);
}

void print(int** a, int r, int c, int p = 0) {
    if (p == r * c) return;
    cout << setw(5) << a[p / c][p % c];
    if (p % c == c - 1) cout << '\n';
    print(a, r, c, p + 1);
}

bool selected(int x) {
    return !(x > 0 && x % 5 == 0);
}

void countSum(int** a, int r, int c, int& k, int& s, int p = 0) {
    if (p == r * c) return;
    int x = a[p / c][p % c];
    if (selected(x)) { k++; s += x; }
    countSum(a, r, c, k, s, p + 1);
}

void replace(int** a, int r, int c, int p = 0) {
    if (p == r * c) return;
    int& x = a[p / c][p % c];
    if (selected(x)) x = 0;
    replace(a, r, c, p + 1);
}

bool greaterRow(int* x, int* y) {
    if (x[0] != y[0]) return x[0] > y[0];
    if (x[1] != y[1]) return x[1] < y[1];
    return x[2] > y[2];
}

void sortPass(int** a, int n, int j = 0) {
    if (j == n - 1) return;
    if (greaterRow(a[j], a[j + 1])) {
        int* t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
    }
    sortPass(a, n, j + 1);
}

void sortRows(int** a, int n) {
    if (n <= 1) return;
    sortPass(a, n);
    sortRows(a, n - 1);
}

int main() {
    srand(3);
    const int r = 7, c = 6;
    int** a = makeMatrix(r, c);
    fill(a, r, c);

    cout << "Original matrix:\n";
    print(a, r, c);

    int k = 0, s = 0;
    countSum(a, r, c, k, s);
    cout << "Count = " << k << ", Sum = " << s << '\n';

    replace(a, r, c);
    cout << "Zeroed matrix:\n";
    print(a, r, c);
    freeMatrix(a, r);

    srand(3);
    a = makeMatrix(r, c);
    fill(a, r, c);
    cout << "Before sorting:\n";
    print(a, r, c);

    sortRows(a, r);
    cout << "After sorting:\n";
    print(a, r, c);

    freeMatrix(a, r);
    return 0;
}
