#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>

using namespace std;


enum ConsoleColor
{
        Black         = 0,
        Blue          = 1,
        Green         = 2,
        Cyan          = 3,
        Red           = 4,
        Magenta       = 5,
        Brown         = 6,
        LightGray     = 7,
        DarkGray      = 8,
        LightBlue     = 9,
        LightGreen    = 10,
        LightCyan     = 11,
        LightRed      = 12,
        LightMagenta  = 13,
        Yellow        = 14,
        White         = 15
};


void set_color(ConsoleColor text)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | text));
}


void sleep_micro(int milliseconds){
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end){}
}


void print_array(int *nums, int size){
    for (int i = 0; i < size; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");
}


void print_color_array(int *nums, int size, int i_past, int i_new){
    for (int i = 0; i < size; i++){
        if (i == i_past){
            set_color(Green);
        }else if (i == i_new){
            set_color(Blue);
        }
        printf("%d ", nums[i]);
        set_color(White);
    }
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void clear_last_line_console(){
    printf("%c[2K", 27);
    printf("\r");
}


int bubble_sort(int *nums, int size){
    int c = 0;
    bool swapped;
    for(int i = 0; i < size-1; i++){
        swapped = false;
        for (int j = 0; j < size - 1 - i; j++){
            if (nums[j] > nums[j+1]){
                swap(&nums[j], &nums[j+1]);
                c += 1;
                clear_last_line_console();
                print_color_array(nums, size, j, j+1);
                swapped = true;
                sleep_micro(600);
            }
        }
        if (!swapped)break;
    }
    printf("\n");
    return c;
}


int isertion_sort(int *nums, int size){
    int c = 0;
    for (int i = 1; i < size; i++){
        for (int j = i; j > 0; j--){
            if (nums[j-1] > nums[j]){
                swap(&nums[j], &nums[j-1]);
                c += 1;
                clear_last_line_console();
                print_color_array(nums, size, j-1, j);
                sleep_micro(600);
            }else break;
        }
    }
    printf("\n");
    return c;
}


int quick_sort(int *nums, int size){
    int i = 0;
    int j = 0;
    int left = 0,
    int right = 0;
    int middle = 0;
}


const int NUMS_SIZE = 15;


int main(){
    setlocale(LC_ALL,"RUSSIAN");
    set_color(White);

    int nums[NUMS_SIZE] = {};
    for (int i = 0; i < NUMS_SIZE; i++){
        nums[i] = rand() % 1000;
    }
    printf("Rand nums: ");
    print_array(nums, NUMS_SIZE);

    int sort_num = 0;
    printf("Put algorithm num\n1) Bubble sort\n2) Isertion Sort\n3) Quick sort\nAlgo num: ");
    scanf("%d", &sort_num);
    int c_operations = 0;
    switch (sort_num) {
        case 1:
            c_operations = bubble_sort(nums, NUMS_SIZE);
            break;
        case 2:
            c_operations = isertion_sort(nums, NUMS_SIZE);
            break;
    }
    clear_last_line_console();
    printf("Operations amount is %d\n", c_operations);
    printf("Sorted nums: ");
    print_array(nums, NUMS_SIZE);

    system("pause");
    return 0;
}
