#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "tasks.h"

int main() {
    
    Stack* main_stack = init_stack();

    while (1) {
        printf("\nМеню:\n");
        printf("1 - Найти минимальный элемент в стеке (Задание 1)\n");
        printf("2 - Объединить два стека (Задание 2)\n");
        printf("3 - Вычисление выражений из файла (Задание 3)\n");
        printf("4 - Просмотреть содержимое стека\n");
        printf("0 - Выйти из программы\n");

        int choice = get_valid_int("Ваш выбор: ");
        switch (choice) {
            case 1:
                task_min_element(main_stack);
                break;
            case 2: {
                Stack* merged = task_merge_stacks();
                if (merged) {
                    printf("Объединённый стек (упорядоченный по возрастанию):\n");
                    print_stack(merged);
                    free_stack(merged);
                }
                break;
            }
            case 3: {
                char infile[100], outfile[100];
                printf("Введите имя входного файла: ");
                scanf("%99s", infile);
                printf("Введите имя выходного файла: ");
                scanf("%99s", outfile);
                task_eval_file(infile, outfile);
                break;
            }
            case 4:
                printf("Просмотр содержимого общего стека:\n");
                print_stack(main_stack);
                break;
            case 0:
                printf("Выход из программы.\n");
                free_stack(main_stack);
                exit(0);
            default:
                printf("Неверный выбор.\n");
        }
    }
    return 0;
}
