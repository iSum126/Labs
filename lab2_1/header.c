#include <stdio.h>

void int_check(int *num) {

    char c;
    while( scanf("%d%c", num, &c) != 2 || c != '\n' ) {
        printf("Некорректный ввод, попробуйте ещё раз.\n");
        while (getchar() != '\n');
    }

}

void array_input(int* arr, int n) {
    int check_num = 0;
    char choice;

    printf("Выберите нужный вам способ заполнения массива.\n");
    printf("Введите 1 если вы хотите ввести элементы массива самостоятельно.\n");
    printf("Введите 2 если вы хотите заполнить массив с помощью генератора случайных чисел.\n");
    
    scanf("%c", &choice);

    while (choice != '1' && choice != '2') {
        printf("Некорректный ввод. Попробуйте ещё раз.\n");
        scanf("%c", &choice);
    }

    if (choice == '1') {
        printf("Выбран режим ручного заполнения массива.\n");
        for (int i = 0; i < n; i++) {

            printf("Введите элемент с индексом %d: ", i);
            int_check(&arr[i]);

        }
    }

    else if (choice == '2') {
        srand(time(NULL));
        int min, max;
        printf("Выбран режим заполнения с помощью генератора случайных чисел.\n");
        
        do {
            printf("Введите нижний порог заполнения: ");
            int_check(&min);

            printf("Введите верхний порог заполнения: ");
            int_check(&max);

            if (min > max) {
                printf("Нижний порог заполнения не может быть больше верхнего. Попробуйте ещё раз.\n");
            }
        } while (min > max);

        //непосредственно заполнение
        for (int i = 0; i < n; i++) {
            arr[i] = min + rand() % (max - min - 1);
        }
    }
}

void array_output(int* arr, int n) {
    
    printf("Полученный массив: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

}

void bubble_sort(int* arr, int n, int x) {

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] < arr[j+1] && arr[j] >= x) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

}