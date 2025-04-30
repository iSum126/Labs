#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "tasks.h"

int main() {
    while (1) {
        printf("\nМеню:\n");
        printf("1 - Задание 1: Очередь символов\n");
        printf("2 - Задание 2: Дек символов\n");
        printf("3 - Задание 3: Анализ строки и очереди чисел\n");
        printf("4 - Просмотр результатов предыдущих заданий (результат выводится сразу после выполнения)\n");
        printf("0 - Выход из программы\n");

        int choice = get_valid_int("Ваш выбор: ");
        switch(choice) {
            case 1:
                task_char_queue();
                break;
            case 2:
                task_char_deque();
                break;
            case 3:
                task_string_analysis();
                break;
            case 4:
                printf("Результаты каждого задания выводятся сразу после его выполнения.\n");
                break;
            case 0:
                printf("Выход из программы.\n");
                exit(0);
            default:
                printf("Неверный выбор.\n");
        }
    }
    return 0;
}
