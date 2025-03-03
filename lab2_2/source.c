#include <stdio.h>

void file_input(char *file_name) {

    FILE *file = fopen(file_name, "w");

    if(file == NULL) {
        perror("Ошибка!");
        exit(1);
    }

    printf("Введите данные:\n");

    char ch;

    while( (ch = getchar()) != '\n' ) {
        fputc(ch, file);
    }
    
    fputc('\n', file);

    fclose(file);
}

void file_output(char* file_name) {

    FILE *file = fopen(file_name, "r");

    if(file == NULL) {
        perror("Ошибка!");
        exit(1);
    }

    char ch;

    printf("Содержимое файла:\n");

    while ((ch = fgetc(file)) != EOF) { 
        putchar(ch);
    }

    fclose(file);
}

void char_counter(char *file_name) {
    
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        perror("Ошибка открытия файла!!");
        exit(1);
    }

    int counter[256] = {0};

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        counter[(unsigned char)ch]++;
    }

    printf("Частота встречаемости символов в файле:\n");

    for (int i = 0; i < 256; i++) {
        if (counter[i] > 0) {
            if(i != '\n')
            printf("Символ '%c' встречается %d раз(а)\n", i, counter[i]);
        }
    }

    fclose(file);
}

void space_replace(char* file_name) {

    FILE *file = fopen(file_name, "r+");

    if(file == NULL) {
        perror("Ошибка открытия файла!!");
        exit(1);
    }

    char ch, repl_ch;

    printf("Введите символ для замены: ");
    scanf("%c", &repl_ch);

    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ') {
            fseek(file, -1, SEEK_CUR);  
            fputc(repl_ch, file);
        }
    }

    fclose(file);
}

