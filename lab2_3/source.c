#include <stdio.h>

typedef struct Char_bit_field {
    unsigned last_bits : 4;
} Char_bit_field;

typedef struct Goverment {
    char type[100];
} Goverment;

typedef struct Countries {
    char name[100];
    unsigned population;
    Goverment goverment;
    char capital[50];
} Countries;

void print_char_last_bits(unsigned ch, int bits) {
    for(int i = bits - 1; i >= 0; i--) {
        printf("%d", (ch >> i) & 1);
    }
    printf("\n");
}

void task_1() {
    char ch;
    printf("Введите символ: ");
    scanf("%c", &ch);
    
    Char_bit_field cbf;
    cbf.last_bits = ch & 0b1111;

    printf("Младшие 4 бита: ");
    print_char_last_bits(cbf.last_bits, 4);
}

void task_2() {

}