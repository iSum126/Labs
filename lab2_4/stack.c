#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* init_stack() {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    if (!s) {
        printf("Ошибка выделения памяти для int стека.\n");
        exit(EXIT_FAILURE);
    }
    s->data = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    if (!s->data) {
        printf("Ошибка выделения памяти для данных int стека.\n");
        free(s);
        exit(EXIT_FAILURE);
    }
    s->top = -1;
    s->capacity = INITIAL_CAPACITY;
    return s;
}

void free_stack(Stack* stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

int is_empty(Stack* stack) {
    return stack->top == -1;
}

int is_full(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, int value) {
    if (is_full(stack)) {
        stack->capacity *= 2;
        int* new_data = realloc(stack->data, stack->capacity * sizeof(int));
        if (!new_data) {
            printf("Ошибка перераспределения памяти для int стека.\n");
            free_stack(stack);
            exit(EXIT_FAILURE);
        }
        stack->data = new_data;
    }
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Стек пуст, невозможно извлечь элемент.\n");
        return -1;
    }
    return stack->data[stack->top--];
}

int peek(Stack* stack) {
    if (is_empty(stack)) {
        printf("Стек пуст, нет верхнего элемента.\n");
        return -1;
    }
    return stack->data[stack->top];
}

void print_stack(Stack* stack) {
    if (is_empty(stack)) {
        printf("Стек пуст.\n");
        return;
    }
    printf("Содержимое стека (сверху вниз):\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->data[i]);
    }
}

int get_valid_int(const char* prompt) {
    int value;
    char ch;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &value, &ch) != 2 || ch != '\n') {
            printf("Некорректный ввод. Попробуйте снова.\n");
            while (getchar() != '\n');
        } else {
            return value;
        }
    }
}


StackDouble* init_stack_double() {
    StackDouble* s = (StackDouble*)malloc(sizeof(StackDouble));
    if (!s) {
        printf("Ошибка выделения памяти для double стека.\n");
        exit(EXIT_FAILURE);
    }
    s->data = (double*)malloc(INITIAL_CAPACITY * sizeof(double));
    if (!s->data) {
        printf("Ошибка выделения памяти для данных double стека.\n");
        free(s);
        exit(EXIT_FAILURE);
    }
    s->top = -1;
    s->capacity = INITIAL_CAPACITY;
    return s;
}

void free_stack_double(StackDouble* stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

int is_empty_double(StackDouble* stack) {
    return stack->top == -1;
}

int is_full_double(StackDouble* stack) {
    return stack->top == stack->capacity - 1;
}

void push_double(StackDouble* stack, double value) {
    if (is_full_double(stack)) {
        stack->capacity *= 2;
        double* new_data = realloc(stack->data, stack->capacity * sizeof(double));
        if (!new_data) {
            printf("Ошибка перераспределения памяти для double стека.\n");
            free_stack_double(stack);
            exit(EXIT_FAILURE);
        }
        stack->data = new_data;
    }
    stack->data[++stack->top] = value;
}

double pop_double(StackDouble* stack) {
    if (is_empty_double(stack)) {
        printf("Double стек пуст, невозможно извлечь элемент.\n");
        return 0;
    }
    return stack->data[stack->top--];
}

double peek_double(StackDouble* stack) {
    if (is_empty_double(stack)) {
        printf("Double стек пуст, нет верхнего элемента.\n");
        return 0;
    }
    return stack->data[stack->top];
}


StackChar* init_stack_char() {
    StackChar* s = (StackChar*)malloc(sizeof(StackChar));
    if (!s) {
        printf("Ошибка выделения памяти для char стека.\n");
        exit(EXIT_FAILURE);
    }
    s->data = (char*)malloc(INITIAL_CAPACITY * sizeof(char));
    if (!s->data) {
        printf("Ошибка выделения памяти для данных char стека.\n");
        free(s);
        exit(EXIT_FAILURE);
    }
    s->top = -1;
    s->capacity = INITIAL_CAPACITY;
    return s;
}

void free_stack_char(StackChar* stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

int is_empty_char(StackChar* stack) {
    return stack->top == -1;
}

int is_full_char(StackChar* stack) {
    return stack->top == stack->capacity - 1;
}

void push_char(StackChar* stack, char value) {
    if (is_full_char(stack)) {
        stack->capacity *= 2;
        char* new_data = realloc(stack->data, stack->capacity * sizeof(char));
        if (!new_data) {
            printf("Ошибка перераспределения памяти для char стека.\n");
            free_stack_char(stack);
            exit(EXIT_FAILURE);
        }
        stack->data = new_data;
    }
    stack->data[++stack->top] = value;
}

char pop_char(StackChar* stack) {
    if (is_empty_char(stack)) {
        printf("Char стек пуст, невозможно извлечь элемент.\n");
        return '\0';
    }
    return stack->data[stack->top--];
}

char peek_char(StackChar* stack) {
    if (is_empty_char(stack)) {
        printf("Char стек пуст, нет верхнего элемента.\n");
        return '\0';
    }
    return stack->data[stack->top];
}
