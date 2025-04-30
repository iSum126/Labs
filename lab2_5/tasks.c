#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "queue.h"

void task_char_queue() {
    int maxSize = get_valid_int("Введите максимальный размер очереди символов: ");
    CharQueue *queue = init_char_queue(maxSize);
    
    char etalon;
    printf("Введите эталонный символ: ");
    scanf(" %c", &etalon);
    
    printf("Вводите символы для очереди (ввод прекращается при встрече эталонного символа '%c').\n", etalon);
    while (1) {
        char ch;
        printf("Введите символ: ");
        scanf(" %c", &ch);
        if (ch == etalon)
            break;
        enqueue_char(queue, ch);
    }
    
    printf("Размер очереди: %d\n", size_char_queue(queue));
    printf("Содержимое очереди:\n");
    print_char_queue(queue);
    free_char_queue(queue);
}

void task_char_deque() {
    int maxSize = get_valid_int("Введите максимальный размер дека символов: ");
    CharDeque *deque = init_char_deque(maxSize);
    
    char etalon;
    printf("Введите эталонный символ: ");
    scanf(" %c", &etalon);
    
    printf("Вводите символы для дека (ввод прекращается при встрече эталонного символа '%c').\n", etalon);
    int turn = 0;
    while (1) {
        char ch;
        printf("Введите символ: ");
        scanf(" %c", &ch);
        if (ch == etalon)
            break;
        if (turn % 2 == 0)
            push_right(deque, ch);
        else
            push_left(deque, ch);
        turn++;
    }
    
    printf("Размер дека: %d\n", size_char_deque(deque));
    printf("Содержимое дека:\n");
    print_char_deque(deque);
    free_char_deque(deque);
}

void task_string_analysis() {
    char inputString[256];
    while(getchar() != '\n');
    printf("Введите строку, содержащую числа, разделенные пробелами: ");
    fgets(inputString, sizeof(inputString), stdin);
    inputString[strcspn(inputString, "\n")] = '\0';
    
    IntQueue *oneDigitQueue = init_int_queue(10);
    IntQueue *twoDigitQueue = init_int_queue(10);
    
    char *token = strtok(inputString, " ");
    while (token != NULL) {
        int num = atoi(token);
        if (num >= -9 && num <= 9)
            enqueue_int(oneDigitQueue, num);
        else if ((num >= 10 && num <= 99) || (num <= -10 && num >= -99))
            enqueue_int(twoDigitQueue, num);
        token = strtok(NULL, " ");
    }
    
    printf("Очередь однозначных чисел:\n");
    print_int_queue(oneDigitQueue);
    printf("Очередь двузначных чисел:\n");
    print_int_queue(twoDigitQueue);
    
    int minSize = size_int_queue(oneDigitQueue) < size_int_queue(twoDigitQueue) ?
                  size_int_queue(oneDigitQueue) : size_int_queue(twoDigitQueue);
    
    IntQueue *resultQueue = init_int_queue(10);
    for (int i = 0; i < minSize; i++) {
        int a = dequeue_int(oneDigitQueue);
        int b = dequeue_int(twoDigitQueue);
        int product = a * b;
        enqueue_int(resultQueue, product);
    }
    
    printf("Очередь произведений соответствующих элементов:\n");
    print_int_queue(resultQueue);
    
    free_int_queue(oneDigitQueue);
    free_int_queue(twoDigitQueue);
    free_int_queue(resultQueue);
}
