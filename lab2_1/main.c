#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "header.c"

int main(int argc, char *argv[]) {

    //1-е задание
    setlocale(LC_ALL, "Rus");
    if (argc < 2) {
        perror("Ошибка! Вы не передали файл!\n");
        return 1;
    }
    printf("\033[2J\033[1;1H"); //очистка для линукса

    FILE *file = fopen(argv[1], "w+b");

    if (file == NULL) {
        perror("Ошибка открытия файла!");
        return 1;
    }

    int n;

    printf("Введите желаемое количество элементов массива: ");
    do {
        int_check(&n);
    } while (n < INT_MIN);

    int *arr = (int*)malloc(n * sizeof(int));
    if(arr == NULL) {
        perror("Ошибка выделения памяти!\n");
        fclose(file);
        return 1;
    }

    array_input(arr, n);
 

    fwrite(arr, sizeof(arr[0]), n, file);

    free(arr);
    arr = NULL;

    arr = (int*)malloc(n * sizeof(int));
    rewind(file);
    fread(arr, sizeof(int), n, file);

    array_output(arr, n);

    fclose(file);

    //2-е, 3-е задания

    int sum = 0;
    int even_num = 0;

    //часть 2-го задания
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0) {
            sum += arr[i];
            even_num += 1;
        }
    }

    //часть 3-го задания
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
            arr[j++] = arr[i];
        }
    }
    n = j;

    printf("Сумма всех чётных чисел: %d\n", sum);

    int *temp = realloc(arr, n * sizeof(int));

    if (temp != NULL) {  
        arr = temp;
    } else {
        perror("Ошибка перевыделения памяти!");  
        return 1;
    }

    printf("Было выполнено удаление чётных элементов из массива.\n");
    array_output(arr, n);

    //4-е задание(доделать)

    int x;
    int x_amm = 0;
    printf("Введите заданное число(по условию задания №4):  ");
    int_check(&x);
    printf("\n");

    //сортировка элементов > x
    bubble_sort(arr, n, x);
    
    printf("Была выполнена сортировка элементов, которые больше чем %d\n", x);
    array_output(arr, n);

    //запись результата в файл
    file = fopen(argv[1], "wb");
    fwrite(arr, sizeof(arr[0]), n, file);
    fclose(file);
    free(arr);

    return 0;
}
