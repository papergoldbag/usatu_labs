// Вариант 3
#include <iostream>
using namespace std;


int R = 15; // Вместимость рюкзака
int a[] = { 5,  1,  2,  3,  9, 3,  6,  1 }; // Веса
int b[] = { 20, 15, 15, 32, 4, 20, 27, 1 }; // Цены
const int n = sizeof(a) / sizeof(int);
int vbest[100][n]; // Вывод
int kbest = 0;
int V[n]; // Массив для построения вариантов
int record = 0; // Рекордная цена
int rec = 0; // Рекордный индекс


void mark() {
	int sum = 0; // Вес, полученный при оценке
	int cena = 0; // Цена
	for (int i = 0; i < n; ++i) {
		sum += V[i] * a[i];
		cena += V[i] * b[i];
	}
	if (sum > R) return;

	if (cena > record) {
		record = cena;
		kbest = 0;
	}
	if (kbest < 100)
		for (int i = 0; i < n; ++i)
			vbest[kbest][i] = V[i];

	kbest++;  //переводит на первую строку, остальное выкидывает в мусор
}

int next() {  //функция строит новую выборку
	for (int i = n - 1; i >= 0; --i)
		if (V[i]) V[i] = 0;
		else {
			V[i] = 1;
			return 1;
		}
	return 0;
}
void print() {
	cout << "Вместимость рюказака: " << R << endl << "Возможные комбинации: ";
	for (int i = 0; i < kbest; ++i) {
		cout << endl;
		for (int j = 0; j < n; ++j)
			if (vbest[i][j] * a[j] != 0)
				cout << vbest[i][j] * a[j] << " ";
	}
	cout << endl;
	cout << "Максимальная стоимость" << "\n" << record << " " << "При следующих весах" << endl;

	for (int j = 0; j < n; ++j)
		if (vbest[rec][j] * a[j] != 0) {
			cout << vbest[rec][j] * a[j] << " ";
		}
}
int main() {
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < n; ++i)
		V[i] = 0;
	V[n - 1] = 1;
	cout << "Массив весов" << endl;
	for (int i = 0; i < 8; i++)
		printf("%5d", a[i]);

	cout << endl;
	cout << "Массив стоимостей" << endl;
	for (int i = 0; i < 8; i++)
		printf("%5d", b[i]);

	cout << endl;
	do {
		mark();
	} while (next());  // будет добавлять единицу
	print();
}
