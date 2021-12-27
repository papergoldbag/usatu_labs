#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))


void remove_matrix(int** matrix, int size){
  for (int i = 0; i<size; i ++)
    free(matrix[i]);
  free(matrix);
}


int* create_array(int size){
  return (int*) calloc(size, sizeof(int));
}


int** create_matrix(int size){
  int **matrix = (int**)calloc(size, sizeof(int*));
  for (int i = 0; i < size; i++){
    matrix[i] = create_array(size);
  }
  return matrix;
}


int** copy_matrix(int** matrix, int size){
  int **copy_matrix = create_matrix(size);
  for (int i = 0; i<size; i++){
    for (int j = 0; j < size; j++){
      copy_matrix[i][j] = matrix[i][j];
    }
  }
  return copy_matrix;
}


void print_matrix(int** matrix, int size){
  double t = 0;
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      printf("%d\t", matrix[i][j]);
    }
    printf("\n");
  }
}


void input_matrix(int** matrix, int size){
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      printf("[%d][%d]=", i+1, j+1);
      scanf("%d", &matrix[i][j]);
    }
  }
}


void input_rand_matrix(int** matrix, int size){
  srand(time(NULL));
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      if (i == j) matrix[i][j] = 0;
      else matrix[i][j] = rand() % 100;
    }
  }
}


void input_file_matrix(char *filename, int** matrix, int size){
  FILE *file = fopen(filename, "r");
  if (file == NULL){
    perror("Не удалось открыть файл");
    exit(-1);
  }

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      fscanf(file, "%d ", &matrix[i][j]);

  fclose(file);
}


void matrix_to_file(char *filename, int** matrix, int size){
  FILE *file = fopen(filename, "w");
  if (file == NULL){
    perror("Не удалось открыть файл");
    exit(-1);
  }

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      fprintf(file, "%d ", matrix[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);
}


void print_moves(int **matrix, int **mkr, int size){
  int i1;
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      if (i == j || matrix[i][j] == mkr[i][j])
        continue;

      printf("%d -> %d (%d):\n %d ->", i, j, mkr[i][j], i);

      i1 = i;
      do{
        for (int k = 0; k < size; k++){
          if ((matrix[i1][k] > 0) && ((matrix[i1][k] + mkr[k][j]) == mkr[i1][j]) || (k == j) && (matrix[i1][k] == mkr[i1][j])){
            printf("   %d (%d)->", k, matrix[i1][k]);
            i1 = k;
            break;
          }
        }
      } while (i1 != j);
      printf("\b\b \n");
    }
  }
}


int** floydmatrix(int **matrix, int n) {
  int ** res_matrix = copy_matrix(matrix, n);
  for(int k=0 ; k<n ; k++ ){
    for(int i=0 ; i<n ; i++ ){
      for(int j=0 ; j<n ; j++ ){
        if(i != j && res_matrix[i][k] != -1 && res_matrix[k][j] != -1){
          if(res_matrix[i][j] == -1){
            res_matrix[i][j] = res_matrix[i][k] + res_matrix[k][j];
          }else{
            res_matrix[i][j] = min(res_matrix[i][j], res_matrix[i][k] + res_matrix[k][j]);
          }
        }
      }
    }
  }
  return res_matrix;
}


int main(){
  // Matrix
  int size = 0;
  printf("Введите размерность матрицы А:");
  scanf("%d", &size);

  int **matrix = create_matrix(size);

  int input_mode = 0;
  printf("Задать значения элементов матрицы А вручную(1), случайным образом(2) или файлом(3)?");
  scanf("%d", &input_mode);
  if (input_mode == 1){
    printf("Если дороги нет, то пишите -1\n");
    input_matrix(matrix, size);
  }else if (input_mode == 2){
    input_rand_matrix(matrix, size);
  }else if (input_mode == 3){
    input_file_matrix("./input_matrix.txt", matrix, size);
  }else{
    return -1;
  }

  printf("Исходная матрица:\n");
  print_matrix(matrix, size);

  // Floyd process
  char *filename_output = "./matrix_output.txt";
  int ** mkr = floydmatrix(matrix, size);
  printf("Матрица кратчайших расстояний:\n");
  print_matrix(mkr, size);
  matrix_to_file(filename_output, mkr, size);
  printf("Матрица кратчайших расстояний записана в файле %s\n", filename_output);

  // moves
  printf("Составные пути:\n");
  print_moves(matrix, mkr, size);

  // removing dy arrays
  remove_matrix(matrix, size);
  remove_matrix(mkr, size);

  return 0;
}
