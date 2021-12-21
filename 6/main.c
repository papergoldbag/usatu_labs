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
  

  return 0;
}
