#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "source.c"

int main(int argc, char* argv[]) {

    printf("\033[2J\033[1;1H"); //очистка для линукса

    if(argc != 2) {
        perror("Ошибка передачи файла!\n");
        exit(1);
    }
    
    char *file = argv[1];

    file_input(file);
    file_output(file);

    char_counter(file);

    space_replace(file);
    printf("Файл с заменёнными символами:\n");
    file_output(file);

    
    return 0;
}