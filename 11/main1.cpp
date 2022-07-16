#include <iostream>
using namespace std;


int R = 15;
int a[] = { 5, 5, 4, 3, 12, 7, 2 };
const int n = sizeof(a) / sizeof(int);
int vbest[100][n];
int kbest = 0;
// Количество лучших
int v[n];
// Промежуточная выборка
int record = 0;
// Рекорд заполняемости


void mark() {
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += v[i] * a[i];
    if (sum > R)
        return;
    if (sum < record)
        return;
    if (sum > record) {
        record = sum;
        kbest = 0;
    }
    if (kbest < 100)
        for (int i = 0; i < n; ++i)
            vbest[kbest][i] = v[i];
    kbest++;
}

int next() {
    for (int i = n - 1; i >= 0; --i)
        if (v[i])
            v[i] = 0;
        else {
            v[i] = 1;
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
}

int main() {
    setlocale(LC_ALL, "Rus");

    for (int i = 0; i < n; ++i) v[i] = 0;
    v[n - 1] = 1;

    do {
        mark();
    } while (next());

    cout << "Лучшие комбинации при размере рюкзака " << R << '\n';
    print_info();
}
