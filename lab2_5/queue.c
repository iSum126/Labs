#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/* ------------------ Очередь символов ------------------ */
CharQueue* init_char_queue(int capacity) {
    CharQueue *queue = (CharQueue*)malloc(sizeof(CharQueue));
    if (!queue) {
        printf("Ошибка выделения памяти для очереди символов.\n");
        exit(EXIT_FAILURE);
    }
    queue->data = (char*)malloc(capacity * sizeof(char));
    if (!queue->data) {
        printf("Ошибка выделения памяти для данных очереди символов.\n");
        free(queue);
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

void free_char_queue(CharQueue *queue) {
    if (queue) {
        free(queue->data);
        free(queue);
    }
}

int is_empty_char_queue(CharQueue *queue) {
    return (queue->size == 0);
}

int is_full_char_queue(CharQueue *queue) {
    return (queue->size == queue->capacity);
}

void enqueue_char(CharQueue *queue, char value) {
    if (is_full_char_queue(queue)) {
        printf("Очередь заполнена, невозможно добавить символ '%c'.\n", value);
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

char dequeue_char(CharQueue *queue) {
    if (is_empty_char_queue(queue)) {
        printf("Очередь пуста, невозможно удалить элемент.\n");
        return '\0';
    }
    char value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

int size_char_queue(CharQueue *queue) {
    return queue->size;
}

void print_char_queue(CharQueue *queue) {
    if (is_empty_char_queue(queue)) {
        printf("Очередь пуста.\n");
        return;
    }
    printf("Содержимое очереди (от начала до конца): ");
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % queue->capacity;
        printf("%c ", queue->data[index]);
    }
    printf("\n");
}

/* ------------------ Дек символов ------------------ */
CharDeque* init_char_deque(int capacity) {
    CharDeque *deque = (CharDeque*)malloc(sizeof(CharDeque));
    if (!deque) {
        printf("Ошибка выделения памяти для дека.\n");
        exit(EXIT_FAILURE);
    }
    deque->data = (char*)malloc(capacity * sizeof(char));
    if (!deque->data) {
        printf("Ошибка выделения памяти для данных дека.\n");
        free(deque);
        exit(EXIT_FAILURE);
    }
    deque->capacity = capacity;
    deque->size = 0;
    // Инициализация по кругу: front – начальный индекс, rear – последний возможный индекс
    deque->front = 0;
    deque->rear = capacity - 1;
    return deque;
}

void free_char_deque(CharDeque *deque) {
    if (deque) {
        free(deque->data);
        free(deque);
    }
}

int is_empty_char_deque(CharDeque *deque) {
    return (deque->size == 0);
}

int is_full_char_deque(CharDeque *deque) {
    return (deque->size == deque->capacity);
}

void push_left(CharDeque *deque, char value) {
    if (is_full_char_deque(deque)) {
        printf("Дек заполнен, невозможно добавить символ '%c' слева.\n", value);
        return;
    }
    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    deque->data[deque->front] = value;
    deque->size++;
}

void push_right(CharDeque *deque, char value) {
    if (is_full_char_deque(deque)) {
        printf("Дек заполнен, невозможно добавить символ '%c' справа.\n", value);
        return;
    }
    deque->rear = (deque->rear + 1) % deque->capacity;
    deque->data[deque->rear] = value;
    deque->size++;
}

char pop_left(CharDeque *deque) {
    if (is_empty_char_deque(deque)) {
        printf("Дек пуст, невозможно удалить элемент слева.\n");
        return '\0';
    }
    char value = deque->data[deque->front];
    deque->front = (deque->front + 1) % deque->capacity;
    deque->size--;
    return value;
}

char pop_right(CharDeque *deque) {
    if (is_empty_char_deque(deque)) {
        printf("Дек пуст, невозможно удалить элемент справа.\n");
        return '\0';
    }
    char value = deque->data[deque->rear];
    deque->rear = (deque->rear - 1 + deque->capacity) % deque->capacity;
    deque->size--;
    return value;
}

int size_char_deque(CharDeque *deque) {
    return deque->size;
}

void print_char_deque(CharDeque *deque) {
    if (is_empty_char_deque(deque)) {
        printf("Дек пуст.\n");
        return;
    }
    printf("Содержимое дека (от левого к правому): ");
    int index = deque->front;
    for (int i = 0; i < deque->size; i++) {
        printf("%c ", deque->data[index]);
        index = (index + 1) % deque->capacity;
    }
    printf("\n");
}

/* ------------------ Очередь целых чисел (Task 3) ------------------ */
IntQueue* init_int_queue(int capacity) {
    IntQueue *queue = (IntQueue*)malloc(sizeof(IntQueue));
    if (!queue) {
        printf("Ошибка выделения памяти для очереди чисел.\n");
        exit(EXIT_FAILURE);
    }
    queue->data = (int*)malloc(capacity * sizeof(int));
    if (!queue->data) {
        printf("Ошибка выделения памяти для данных очереди чисел.\n");
        free(queue);
        exit(EXIT_FAILURE);
    }
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

void free_int_queue(IntQueue *queue) {
    if (queue) {
        free(queue->data);
        free(queue);
    }
}

int is_empty_int_queue(IntQueue *queue) {
    return (queue->size == 0);
}

int is_full_int_queue(IntQueue *queue) {
    return (queue->size == queue->capacity);
}

void enqueue_int(IntQueue *queue, int value) {
    if (is_full_int_queue(queue)) {
        /* Для очереди чисел допускаем расширение */
        int new_capacity = queue->capacity * 2;
        int *new_data = realloc(queue->data, new_capacity * sizeof(int));
        if (!new_data) {
            printf("Ошибка перераспределения памяти для очереди чисел.\n");
            free_int_queue(queue);
            exit(EXIT_FAILURE);
        }
        queue->data = new_data;
        queue->capacity = new_capacity;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

int dequeue_int(IntQueue *queue) {
    if (is_empty_int_queue(queue)) {
        printf("Очередь чисел пуста, невозможно удалить элемент.\n");
        return -1;
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

int size_int_queue(IntQueue *queue) {
    return queue->size;
}

void print_int_queue(IntQueue *queue) {
    if (is_empty_int_queue(queue)) {
        printf("Очередь чисел пуста.\n");
        return;
    }
    printf("Содержимое очереди чисел: ");
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % queue->capacity;
        printf("%d ", queue->data[index]);
    }
    printf("\n");
}

/* ------------------ Функция ввода целого числа ------------------ */
int get_valid_int(const char *prompt) {
    int value;
    char term;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &value, &term) != 2 || term != '\n') {
            printf("Некорректный ввод. Повторите попытку.\n");
            while(getchar() != '\n');
        } else {
            return value;
        }
    }
}
