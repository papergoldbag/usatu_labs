#include <stdio.h>
#include <stdlib.h>
#include<time.h>


double* create_array(int size){
  return (double*) calloc(size, sizeof(double));
}


double** create_matrix(int strings, int columns){
  double **matrix = (double**)calloc(strings, sizeof(double*));
  for (int i = 0; i < strings; i++){
    matrix[i] = create_array(columns);
  }
  return matrix;
}


void input_matrix(double** matrix, int strings, int columns){
  double tmp = 0;
  for (int i = 0; i < strings; i++){
    for (int j = 0; j < columns; j++){
      printf("[%d][%d]=", i+1, j+1);
      scanf("%lf", &tmp);
      matrix[i][j] = tmp;
    }
  }
}


void input_rand_matrix(double** matrix, int strings, int columns){
  srand(time(NULL));
  double tmp = 0;
  for (int i = 0; i < strings; i++){
    for (int j = 0; j < columns; j++){
      matrix[i][j] = (double)(rand() % 100);
    }
  }
}


void print_matrix(double** matrix, int strings, int columns){
  for (int i = 0; i < strings; i++){
    for (int j = 0; j < columns; j++){
      printf("%.2lf\t", matrix[i][j]);
    }
    printf("\n");
  }
}


int main(){
  //matrix A
  double **matrix_a;
  int matrix_a_strings, matrix_a_columns, matrix_a_input_mode;
  printf("Введите размерность матрицы А:");
  scanf("%lf", &matrix_a_strings);
  matrix_a_columns = matrix_a_strings;

  printf("Задать значения элементов матрицы А вручную (1) или случайным образом (2)?");
  scanf("%d", &matrix_a_input_mode);
  if (matrix_a_input_mode == 1){
    input_matrix(matrix_a, matrix_a_strings, matrix_a_columns);
  }else{
    input_rand_matrix(matrix_a, matrix_a_strings, matrix_a_columns);
  }

//   Введите размерность матрицы А: ->n
//   Задать значения элементов матрицы А вручную (1) или случайным образом (2)? -
//   >1/2
//   Введите количество столбцов матрицы В: ->mЗадать значения элементов матрицы B вручную (1) или случайным образом (2)? -
//   >1/2
//   A=... B=...
//   det(A)=...
//   A^-1=...
//   X=A^-1*B
//   X=...
//   Проверка:
//   A*X=...
//   A*X-B=...
//   A*A^-1=...
//   A^-1*A=...

  return 0;
}
