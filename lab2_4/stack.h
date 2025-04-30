#ifndef STACK_H
#define STACK_H

#define INITIAL_CAPACITY 10

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

Stack* init_stack();
void free_stack(Stack* stack);
int is_empty(Stack* stack);
int is_full(Stack* stack);
void push(Stack* stack, int value);
int pop(Stack* stack);
int peek(Stack* stack);
void print_stack(Stack* stack);
int get_valid_int(const char* prompt);

typedef struct {
    double *data;
    int top;
    int capacity;
} StackDouble;

StackDouble* init_stack_double();
void free_stack_double(StackDouble* stack);
int is_empty_double(StackDouble* stack);
int is_full_double(StackDouble* stack);
void push_double(StackDouble* stack, double value);
double pop_double(StackDouble* stack);
double peek_double(StackDouble* stack);

typedef struct {
    char *data;
    int top;
    int capacity;
} StackChar;

StackChar* init_stack_char();
void free_stack_char(StackChar* stack);
int is_empty_char(StackChar* stack);
int is_full_char(StackChar* stack);
void push_char(StackChar* stack, char value);
char pop_char(StackChar* stack);
char peek_char(StackChar* stack);

#endif
