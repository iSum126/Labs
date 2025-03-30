#include <stdio.h>
#include "source.c"
#include <string.h>
#include <stdlib.h>

int main(void) {

    int is_open = 1;
    int task_num;
    while(is_open) {
        printf("Введите номер задания");
        int_input_and_check(&task_num);
        switch (task_num)
        {
        case 1:
            task_1();
            break;
        case 2:
            task_2();
            break;
        default:
            printf("Такого задания нет, попробуйте ещё раз.\n");
            break;
        }
    }
    return 0;
}