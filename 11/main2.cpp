//Вариант 2
#include <iostream>
using namespace std;

int R = 18;
int a[] = { 5, 5, 4, 3, 12, 7, 2, 8, 9, 22 };
const int n = sizeof(a) / sizeof(int);
int vbest[100][n];
int kbest = 0;  //кол-во лучших
int v[n];  //промежуточная выборка
int record = 0;   //максимальная заполняемость

void mark(int sum) {
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

void print() {
    for (int i = 0; i < kbest; ++i) {
        for (int j = 0; j < n; ++j)
            if (vbest[i][j] * a[j] != 0)
                cout << vbest[i][j] * a[j] << " ";
        cout << "\n";
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
    print();
    return 0;
}
