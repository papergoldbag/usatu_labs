#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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


void remove_matrix(double** matrix, int strings){
  for (int i = 0; i<strings; i ++)free(matrix[i]);
  free(matrix);
}


void input_matrix(double** matrix, int strings, int columns){
  for (int i = 0; i < strings; i++){
    for (int j = 0; j < columns; j++){
      printf("[%d][%d]=", i+1, j+1);
      scanf("%lf", &matrix[i][j]);
    }
  }
}


void input_rand_matrix(double** matrix, int strings, int columns){
  srand(time(NULL));
  double tmp = 0;
  for (int i = 0; i < strings; i++){
    for (int j = 0; j < columns; j++){
      matrix[i][j] = (double)(rand() % 10);
    }
  }
}


void print_matrix(double** matrix, int strings, int columns){
  double t = 0;
  for (int i = 0; i < strings; i++){
    for (int j = 0; j < columns; j++){
      t = matrix[i][j];
      if ((int)t == 0) t = 0;
      printf("%.2lf\t", t);
    }
    printf("\n");
  }
}


double det(double **matrix, int size) {
    double temp, determinant;
    temp = 0;
    determinant = 1; // to plus

    double **temp_matrix = create_matrix(size, size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            temp_matrix[i][j] = matrix[i][j];

    for (int k = 0; k < size; k++)
        for (int i = k + 1; i < size; i++) {
            temp = temp_matrix[i][k] / temp_matrix[k][k];
            for (int j = 0; j < size; j++)
                temp_matrix[i][j] -= temp_matrix[k][j] * temp;
        }

    for (int i = 0; i < size; i++) determinant *= temp_matrix[i][i];

    remove_matrix(temp_matrix, size);
    if ((int)determinant == 0 || (int)determinant == -0) determinant = 0;
    return determinant;
}


double **inverse_matrix(double **matrix, int size) {
    double temp = 0;
    double** temp_matrix = create_matrix(size, size);
    double** result_matrix = create_matrix(size, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            temp_matrix[i][j] = matrix[i][j];
            if (i == j) result_matrix[i][j] = 1;
            else result_matrix[i][j] = 0;
        }

    for (int k = 0; k < size; k++)
        for (int i = k + 1; i < size; i++) {
            temp = temp_matrix[i][k] / temp_matrix[k][k];
            for (int j = 0; j < size; j++) {
                temp_matrix[i][j] -= temp_matrix[k][j] * temp;
                result_matrix[i][j] -= result_matrix[k][j] * temp;
            }
        }

    for (int k = size - 1; k >= 0; k--)
        for (int i = k - 1; i >= 0; i--) {
            temp = temp_matrix[i][k] / temp_matrix[k][k];
            for (int j = size - 1; j >= 0; j--) {
                temp_matrix[i][j] -= temp_matrix[k][j] * temp;
                result_matrix[i][j] -= result_matrix[k][j] * temp;
            }
        }

    // to 1
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++)
          result_matrix[i][k] /= temp_matrix[i][i];
        temp_matrix[i][i] /= temp_matrix[i][i];
    }

    remove_matrix(temp_matrix, size);
    return result_matrix;
}


double **multiply_matrixes(double **matrix_a, double **matrix_b, int a_strings, int a_columns, int b_strings, int b_columns) {
    double** resultMatrix = create_matrix(a_strings, b_columns);

    if (a_columns != b_strings){
        perror("Ошибка");
        exit(-1);
    }

    for (int i = 0; i < a_strings; i++) {
        for (int j = 0; j < b_columns; j++) {
            resultMatrix[i][j] = 0;
            for (int h = 0; h < a_columns; h++)
                resultMatrix[i][j] += matrix_a[i][h] * matrix_b[h][j];
        }
    }

    return resultMatrix;
}


double ** minus_matrixes(double **matrix_a, double **matrix_b, int strings, int columns){
  double ** matrix = create_matrix(strings, columns);
  for (int i = 0; i<strings; i++){
    for (int j = 0; j<strings; j++){
      matrix[i][j] = matrix_a[i][j] - matrix_b[i][j];
    }
  }
  return matrix;
}


double ** sum_matrixes(double **matrix_a, double **matrix_b, int strings, int columns){
  double ** matrix = create_matrix(strings, columns);
  for (int i = 0; i<strings; i++){
    for (int j = 0; j<strings; j++){
      matrix[i][j] = matrix_a[i][j] + matrix_b[i][j];
    }
  }
  return matrix;
}


int main(){
  //matrix A
  int matrix_a_strings, matrix_a_columns, matrix_a_input_mode;
  printf("Введите размерность матрицы А:");
  scanf("%d", &matrix_a_strings);
  matrix_a_columns = matrix_a_strings;
  double **matrix_a = create_matrix(matrix_a_strings, matrix_a_columns);
  printf("Задать значения элементов матрицы А вручную (1) или случайным образом (2)?");
  scanf("%d", &matrix_a_input_mode);
  if (matrix_a_input_mode == 1){
    input_matrix(matrix_a, matrix_a_strings, matrix_a_columns);
  }else if (matrix_a_input_mode == 2){
    input_rand_matrix(matrix_a, matrix_a_strings, matrix_a_columns);
  }else{
    perror("Choose only 1 or 2");
    exit(-1);
  }

  printf("Матрица A:\n");
  print_matrix(matrix_a, matrix_a_strings, matrix_a_columns);
  printf("\n");

  // Matrix B
  int matrix_b_columns, matrix_b_input_mode;
  printf("Введите количество столбцов матрицы В:");
  scanf("%d", &matrix_b_columns);
  double **matrix_b = create_matrix(matrix_a_strings, matrix_b_columns);
  printf("Задать значения элементов матрицы B вручную (1) или случайным образом (2)?");
  scanf("%d", &matrix_b_input_mode);
  if (matrix_b_input_mode == 1){
    input_matrix(matrix_b, matrix_a_strings, matrix_b_columns);
  }else if (matrix_b_input_mode == 2){
    input_rand_matrix(matrix_b, matrix_a_strings, matrix_b_columns);
  }else{
    perror("Choose only 1 or 2");
    exit(-1);
  }
  printf("Матрица B:\n");
  print_matrix(matrix_b, matrix_a_strings, matrix_b_columns);
  printf("\n");

  // det(A)
  double det_a = det(matrix_a, matrix_a_strings);
  printf("det(A)=%.2lf", det_a);
  printf("\n\n");

  // inverse matrix A
  double **invers_matrix_a = inverse_matrix(matrix_a, matrix_a_strings);
  printf("A^-1:\n");
  print_matrix(invers_matrix_a, matrix_a_strings, matrix_a_strings);
  printf("\n");

  // X=A(^-1)*B
  double **matrix_x = multiply_matrixes(invers_matrix_a, matrix_b, matrix_a_strings, matrix_a_strings, matrix_a_strings, matrix_b_columns);
  printf("X=(A^-1)*B\n");
  printf("X:\n");
  print_matrix(matrix_x, matrix_a_strings, matrix_b_columns);
  printf("\n");

  // check
  printf("Проверка\n");

  // A * X
  double ** matrix_ax = multiply_matrixes(matrix_a, matrix_x, matrix_a_strings, matrix_a_strings, matrix_a_strings, matrix_b_columns);
  printf("A*X:\n");
  print_matrix(matrix_ax, matrix_a_strings, matrix_b_columns);
  printf("\n");

  // A*X-B
  double ** matrix_ax_minus_b = minus_matrixes(matrix_ax, matrix_b, matrix_a_strings, matrix_b_columns);
  printf("A*X-B:\n");
  print_matrix(matrix_ax_minus_b, matrix_a_strings, matrix_a_strings);
  printf("\n");

  // A*(A^-1)
  double ** matrix_a_mul_inv_a = multiply_matrixes(matrix_a, invers_matrix_a, matrix_a_strings, matrix_a_strings, matrix_a_strings, matrix_a_strings);
  printf("A*(A^-1):\n");
  print_matrix(matrix_a_mul_inv_a, matrix_a_strings, matrix_a_strings);
  printf("\n");

  // (A^-1)*A
  double ** matrix_inv_a_mul_a = multiply_matrixes(invers_matrix_a, matrix_a, matrix_a_strings, matrix_a_strings, matrix_a_strings, matrix_a_strings);
  printf("(A^-1)*A:\n");
  print_matrix(matrix_inv_a_mul_a, matrix_a_strings, matrix_a_strings);
  printf("\n");

  return 0;
}
