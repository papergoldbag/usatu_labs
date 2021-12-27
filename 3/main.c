#include <stdio.h>
#include <stdlib.h>


void resheto_eratosphena(int S){
  int N = S + 1;
  int *mas = (int*)malloc(N*sizeof(int));
  for (int i = 2; i <= S; i++) mas[i] = 1;

  //Алгоритм "Решето Эратосфена"
  for (int i = 2; ((i * i) <= S); i++)
    if (mas[i] == 1)
      for (int j = (i * i); j <= S; j += i)
        if (mas[j]==1)
          mas[j] = 0;

  char *file_name = "./resheto_eratosphena.txt";
  FILE *f = fopen(file_name, "w");
  if (f == NULL)
  {
    perror("Не удалось открыть файл");
    exit(-1);
  }
  int block = 100;
  for (int i = 1; i <= S; i++)
    if (mas[i])
      if (i >= block){
        fprintf(f, "\n%d ", i);
        block += 100;
      }else{
        fprintf(f, "%d ", i);
      }
  fclose(f);
}


unsigned long long get_binary(unsigned num) {
    unsigned long long result = num % 2;
    unsigned long long rank = 1;

    while (num /= 2) {
        result += num%2 * (rank *= 10);
    }

    return result;
}


void print_binary(unsigned num){
  unsigned  num2 = get_binary(num);
  int c4 = 0;
  while (num2){
    printf("%llu", num2%10);
    num2 = num2 / 10;
  }
}


int main(){
  // int part = 0;
  // printf("Выберите часть:");
  // scanf("%d", &part);

  // while (1) {
  //   if (part == 1){
  //     int num = 0;
  //     printf("Введите число [-32000, 320000]:");
  //     scanf("%d", &num);
  //   }
  // }

  unsigned n = 10;

  unsigned long long res = get_binary(n);
  print_binary(res);

  return 0;
}
