#include <stdio.h>

typedef struct Char_bit_field {
    unsigned last_bits : 4;
} Char_bit_field;

typedef struct Goverment {
    char type[100];
} Goverment;

typedef struct Country {
    char name[100];
    unsigned population;
    Goverment goverment;
    char capital[50];
    float area;
} Country;

void print_char_last_bits(unsigned ch, int bits) {

    for(int i = bits - 1; i >= 0; i--) {
        printf("%d", (ch >> i) & 1);
    }
    printf("\n");

}

void int_input_and_check(int* num) {
    
    char c;
    while(scanf("%d%c", num, &c) != 2 && c != '\n') {
        while(getchar() != '\n');
        printf("Некорректный ввод, попробуйте ещё раз.\n");
    }

}

void find_country_by_population(Country *countries, int count, long target_population) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (countries[i].population == target_population) {
            printf("Страна: %s, Столица: %s, Население: %ld, Форма правления: %s, Площадь: %.2f кв.км\n",
                   countries[i].name, countries[i].capital, countries[i].population,
                   countries[i].goverment.type, countries[i].area);
            found = 1;
        }
    }
    if (!found) {
        printf("Страны с населением %ld не найдены.\n", target_population);
    }
}

int delete_country_by_capital(Country *countries, int count, const char *target_capital) {
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(countries[i].capital, target_capital) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Страна со столицей %s не найдена.\n", target_capital);
        return count;
    }
    for (int i = index; i < count - 1; i++) {
        countries[i] = countries[i + 1];
    }
    printf("Страна со столицей %s удалена.\n", target_capital);
    return count - 1;
}

void input_country_data(Country *country) {

    printf("Введите название страны: ");
    fgets(country->name, 50, stdin);
    country->name[strcspn(country->name, "\n")] = 0;

    printf("Введите количество жителей: ");
    scanf("%ld", &country->population);
    getchar();

    printf("Введите столицу: ");
    fgets(country->capital, 50, stdin);
    country->capital[strcspn(country->capital, "\n")] = 0;

    printf("Введите форму правления: ");
    fgets(country->goverment.type, 50, stdin);
    country->goverment.type[strcspn(country->goverment.type, "\n")] = 0;

    printf("Введите площадь: ");
    scanf("%f", &country->area);
    getchar();
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

    int country_count;
    printf("Введите кол-во стран: ");
    int_input_and_check(&country_count);

    Country *countries = malloc(country_count * sizeof(Country));
    if (countries == NULL) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    for (int i = 0; i < country_count; i++) {
        printf("\nСтрана %d:\n", i + 1);
        input_country_data(&countries[i]);
    }

    int target_population;
    printf("Введите количество жителей для поиска: ");
    int_input_and_check(&target_population);
    find_country_by_population(countries, country_count, target_population);

    char target_capital[50];
    printf("Введите столицу для удаления страны: ");
    scanf("%s",target_capital);
    country_count = delete_country_by_capital(countries, country_count, target_capital);

    printf("Оставшиеся страны:\n");
    for (int i = 0; i < country_count; i++) {
        printf("Страна: %s, Столица: %s, Население: %ld, Форма правления: %s, Площадь: %.2f кв.км\n",
               countries[i].name, countries[i].capital, countries[i].population,
               countries[i].goverment.type, countries[i].area);
    }

    free(countries);
}