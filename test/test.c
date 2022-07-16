#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct Number {
    int* digits;
    int n;
    int sign;
};



int* create_int_array(int size){
  return (int*) calloc(size, sizeof(int));
}


void _add_zeroes(int *num, int len_1, int len_2, int *new_num) {
    int j = 0;
    for (int i = 0; i < len_1; i++) {
        if (len_1 - len_2 >= i + 1)
            new_num[i] = 0;
        else {
            new_num[i] = num[j];
            j++;
        }
    }
}


void _arrays_summa(int *num_1, int len_1, int *num_2, int len_2, int *num_3) {
    int *new_num_2 = create_int_array(len_1);
    _add_zeroes(num_2, len_1, len_2, new_num_2);

    int memory = 0;

    for (int i = len_1 - 1; i >= 0; i--) {

        int num_high, num_low, new_num;

        num_high = num_1[i];
        num_low = new_num_2[i];

        if (memory == 0) {
            if (num_high + num_low < 10) {
                new_num = num_high + num_low;
                num_3[i+1] = new_num;

            } else {
                memory = 1;
                new_num = num_high + num_low - 10;
                num_3[i+1] = new_num;
            }
        } else {
            if (num_high + num_low + 1 < 10) {
                new_num = num_high + num_low + 1;
                num_3[i+1] = new_num;
                memory = 0;

            } else {
                memory = 1;
                new_num = (num_high + num_low + 1) - 10;
                num_3[i+1] = new_num;
            }
        }
    }
    if(memory==1)
        num_3[0]=1;
    else
        num_3[0]=0;
}


int main(){
  int arr1[6] = {9, 9, 9, 9, 9, 9};
  int arr2[4] = {9, 9, 9, 9};
  int *res = create_int_array(7);
  _arrays_summa(arr1, 6, arr2, 4, res);

  for (int i=0; i<7; i++){
    printf("%d", res[i]);
  }

  return 0;
}
