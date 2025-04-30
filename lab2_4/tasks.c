#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "tasks.h"


static int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void task_min_element(Stack *stack) {
    /* Перед вводом очищаем стек */
    stack->top = -1;
    int size = get_valid_int("Введите размер стека: ");
    if (size <= 0) {
        printf("Недопустимый размер.\n");
        return;
    }
    printf("Введите %d целых чисел:\n", size);
    for (int i = 0; i < size; i++) {
        int val = get_valid_int("> ");
        push(stack, val);
    }
    int min = peek(stack);
    for (int i = 0; i <= stack->top; i++) {
        if (stack->data[i] < min)
            min = stack->data[i];
    }
    printf("Минимальный элемент: %d\n", min);
}

Stack* task_merge_stacks() {

    Stack* s1 = init_stack();
    Stack* s2 = init_stack();
    Stack* result = init_stack();
    Stack* final_stack = init_stack();

    int n1 = get_valid_int("Введите количество элементов 1-го стека (по убыванию): ");
    if(n1 <= 0) {
        printf("Недопустимое количество элементов.\n");
        free_stack(s1); free_stack(s2); free_stack(result); free_stack(final_stack);
        return NULL;
    }
    printf("Введите элементы 1-го стека (по убыванию):\n");
    for (int i = 0; i < n1; i++) {
        int val = get_valid_int("> ");
        push(s1, val);
    }
    
    int n2 = get_valid_int("Введите количество элементов 2-го стека (по возрастанию): ");
    if(n2 <= 0) {
        printf("Недопустимое количество элементов.\n");
        free_stack(s1); free_stack(s2); free_stack(result); free_stack(final_stack);
        return NULL;
    }
    printf("Введите элементы 2-го стека (по возрастанию):\n");
    
    int* temp = (int*)malloc(n2 * sizeof(int));
    if (!temp) {
        printf("Ошибка выделения памяти.\n");
        free_stack(s1); free_stack(s2); free_stack(result); free_stack(final_stack);
        return NULL;
    }
    for (int i = 0; i < n2; i++) {
        temp[i] = get_valid_int("> ");
    }
    
    for (int i = n2 - 1; i >= 0; i--) {
        push(s2, temp[i]);
    }
    free(temp);
    
   
    while (!is_empty(s1) && !is_empty(s2)) {
        if (peek(s1) < peek(s2))
            push(result, pop(s1));
        else
            push(result, pop(s2));
    }
    while (!is_empty(s1))
        push(result, pop(s1));
    while (!is_empty(s2))
        push(result, pop(s2));
    
    
    while (!is_empty(result))
        push(final_stack, pop(result));
    
    free_stack(s1);
    free_stack(s2);
    free_stack(result);
    return final_stack;
}


void task_eval_file(const char *infile, const char *outfile) {
    FILE *fin = fopen(infile, "r");
    FILE *fout = fopen(outfile, "w");
    if (!fin || !fout) {
        printf("Ошибка открытия файлов.\n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), fin)) {

        line[strcspn(line, "\n")] = '\0';
        
        StackDouble* numbers = init_stack_double();
        StackChar* operators = init_stack_char();
        
        int error = 0;
        int error_pos = 0;
        int i = 0;
        int len = (int)strlen(line);
        
        while (i < len && !error) {
            char c = line[i];
            if (c == ' ' || c == '\t') {
                i++;
                continue;
            }
            
            if ((c >= '0' && c <= '9') || c == '.') {
                char *endptr;
                double num = strtod(&line[i], &endptr);
                if (&line[i] == endptr) {
                    error = 1;
                    error_pos = i;
                    break;
                }
                push_double(numbers, num);
                i = (int)(endptr - line);
            }
            else if (c == '(') {
                push_char(operators, c);
                i++;
            }
            else if (c == ')') {
                while (!is_empty_char(operators) && peek_char(operators) != '(') {
                    if (numbers->top < 1) { error = 1; error_pos = i; break; }
                    double b = pop_double(numbers);
                    double a = pop_double(numbers);
                    char op = pop_char(operators);
                    double res;
                    if (op == '+') res = a + b;
                    else if (op == '-') res = a - b;
                    else if (op == '*') res = a * b;
                    else if (op == '/') {
                        if (b == 0) { error = 1; error_pos = i; break; }
                        res = a / b;
                    } else { error = 1; error_pos = i; break; }
                    push_double(numbers, res);
                }
                if (error) break;
                if (is_empty_char(operators)) { error = 1; error_pos = i; break; }
                pop_char(operators);  // удаляем '('
                i++;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/') {
            
                while (!is_empty_char(operators) && peek_char(operators) != '(' &&
                       precedence(peek_char(operators)) >= precedence(c)) {
                    if (numbers->top < 1) { error = 1; error_pos = i; break; }
                    double b = pop_double(numbers);
                    double a = pop_double(numbers);
                    char op = pop_char(operators);
                    double res;
                    if (op == '+') res = a + b;
                    else if (op == '-') res = a - b;
                    else if (op == '*') res = a * b;
                    else if (op == '/') {
                        if (b == 0) { error = 1; error_pos = i; break; }
                        res = a / b;
                    } else { error = 1; error_pos = i; break; }
                    push_double(numbers, res);
                }
                if (error) break;
                push_char(operators, c);
                i++;
            }
            else {
                error = 1;
                error_pos = i;
                break;
            }
        }
        
        while (!is_empty_char(operators) && !error) {
            if (numbers->top < 1) { error = 1; break; }
            double b = pop_double(numbers);
            double a = pop_double(numbers);
            char op = pop_char(operators);
            double res;
            if (op == '+') res = a + b;
            else if (op == '-') res = a - b;
            else if (op == '*') res = a * b;
            else if (op == '/') {
                if (b == 0) { error = 1; break; }
                res = a / b;
            } else { error = 1; break; }
            push_double(numbers, res);
        }
        
        if (error || numbers->top != 0)
            fprintf(fout, "Ошибка в позиции %d\n", error ? error_pos + 1 : i + 1);
        else
            fprintf(fout, "%.2lf\n", peek_double(numbers));
        
        free_stack_double(numbers);
        free_stack_char(operators);
    }
    fclose(fin);
    fclose(fout);
    printf("Результаты записаны в файл \"%s\"\n", outfile);
}
