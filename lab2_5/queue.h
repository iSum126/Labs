#ifndef QUEUE_H
#define QUEUE_H

/* Структура очереди символов (Task 1) */
typedef struct {
    char *data;
    int front;
    int rear;
    int size;
    int capacity;
} CharQueue;

CharQueue* init_char_queue(int capacity);
void free_char_queue(CharQueue *queue);
int is_empty_char_queue(CharQueue *queue);
int is_full_char_queue(CharQueue *queue);
void enqueue_char(CharQueue *queue, char value);
char dequeue_char(CharQueue *queue);
int size_char_queue(CharQueue *queue);
void print_char_queue(CharQueue *queue);

/* Структура дека символов (Task 2) */
typedef struct {
    char *data;
    int front;
    int rear;
    int size;
    int capacity;
} CharDeque;

CharDeque* init_char_deque(int capacity);
void free_char_deque(CharDeque *deque);
int is_empty_char_deque(CharDeque *deque);
int is_full_char_deque(CharDeque *deque);
void push_left(CharDeque *deque, char value);
void push_right(CharDeque *deque, char value);
char pop_left(CharDeque *deque);
char pop_right(CharDeque *deque);
int size_char_deque(CharDeque *deque);
void print_char_deque(CharDeque *deque);

/* Структура очереди целых чисел (Task 3) */
typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} IntQueue;

IntQueue* init_int_queue(int capacity);
void free_int_queue(IntQueue *queue);
int is_empty_int_queue(IntQueue *queue);
int is_full_int_queue(IntQueue *queue);
void enqueue_int(IntQueue *queue, int value);
int dequeue_int(IntQueue *queue);
int size_int_queue(IntQueue *queue);
void print_int_queue(IntQueue *queue);

/* Утилита для ввода целого числа с проверкой */
int get_valid_int(const char *prompt);

#endif