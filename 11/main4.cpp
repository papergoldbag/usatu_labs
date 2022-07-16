//Вариант 4
#include <iostream>
using namespace std;

int R = 18;
int a[] = { 5,  5, 4, 3, 12, 7,  2, 8,  9,  22 }; // Веса
int b[] = { 20, 4, 9, 8, 2,  17, 4, 19, 13, 33};  // Цены
const int n = sizeof(a) / sizeof(int);
int vbest[100][n];
int kbest = 0;       //кол-во лучших
int v[n];            //промежуточная выборка
int record = 0;      //максимальная заполняемость
int rec = 0;
int mxcena = 0;


void mark(int sum) {
    int cena = 0;
    if (sum > R)
        return;

    for (int i = 0; i < n; ++i) {
        cena += v[i] * b[i];
    }
    if (cena > mxcena) {
        kbest = 0;
        mxcena = cena;
    }
    if (kbest < 100)
        for (int i = 0; i < n; ++i)
            vbest[kbest][i] = v[i];
    kbest++;
}

void step_up(int& sum, int first) {
    for (int i = first; i < n; ++i)
        if (a[i] + sum <= R) {
            sum += a[i];
            v[i] = 1;
        }
        else v[i] = 0;
}

int step_back(int& sum, int& first) {
    if (v[n - 1]) {
        sum -= a[n - 1];
        v[n - 1] = 0;
    }
    for (int i = n - 2; i >= 0; --i)
        if (v[i]) {
            sum -= a[i];
            v[i] = 0;
            first = i + 1;
            return 1;
        }
    return 0;

}

void print_info() {
    for (int i = 0; i < kbest; ++i) {
        for (int j = 0; j < n; ++j)
            if (vbest[i][j] * a[j] != 0)
                cout << vbest[i][j] * a[j] << " ";
        cout << "\n";
    }
    cout << "Лучшая комбинация (наибольшая цена " << mxcena << "):\n";
    for (int i = 0; i < n; ++i) {
        if (vbest[0][i] != 0) cout << a[i] << ' ';
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int sum = 0;
    int first = 0;
    do {
        step_up(sum, first);
        mark(sum);
    } while (step_back(sum, first));
    cout << "Лучшие комбинации при размере рюкзака " << R << endl;
    print_info();
    return 0;
}
