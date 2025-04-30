#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"
#include "tree.h"

static int get_valid_int(const char *prompt) {
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

void task_tree_menu(void) {
    TreeNode *T = NULL;
    while (1) {
        printf("\nМеню бинарных деревьев:\n");
        printf("1 - Вставка элемента (создание/дополнение дерева)\n");
        printf("2 - Удаление элемента (введите значение для удаления)\n");
        printf("3 - Визуализация дерева T (сверху вниз)\n");
        printf("4 - Создание идеально сбалансированных деревьев\n");
        printf("      (одно из отрицательных, другое – из неотрицательных)\n");
        printf("0 - Выход\n");

        int choice = get_valid_int("Ваш выбор: ");
        if (choice == 1) {
            int key = get_valid_int("Введите значение для вставки: ");
            T = insert_node(T, key);
            printf("Элемент %d вставлен в дерево.\n", key);
        } else if (choice == 2) {
            int key = get_valid_int("Введите значение для удаления: ");
            T = delete_node(T, key);
            printf("Если элемент %d присутствовал, он удалён.\n", key);
        } else if (choice == 3) {
            printf("Визуализация дерева T (сверху вниз):\n");
            if (T == NULL)
                printf("Дерево пустое.\n");
            else
                print_tree_top_down(T);
        } else if (choice == 4) {
            int total = count_nodes(T);
            if (total == 0) {
                printf("Дерево T пустое. Нечего разбивать.\n");
                continue;
            }
            int *allKeys = (int*)malloc(total * sizeof(int));
            if (!allKeys) {
                printf("Ошибка выделения памяти.\n");
                continue;
            }
            int index = 0;
            inorder_traversal(T, allKeys, &index);
            int negCount = 0, nonNegCount = 0;
            int *negArr = (int*)malloc(total * sizeof(int));
            int *nonNegArr = (int*)malloc(total * sizeof(int));
            if (!negArr || !nonNegArr) {
                printf("Ошибка выделения памяти.\n");
                free(allKeys);
                if (negArr) free(negArr);
                if (nonNegArr) free(nonNegArr);
                continue;
            }
            for (int i = 0; i < total; i++) {
                if (allKeys[i] < 0)
                    negArr[negCount++] = allKeys[i];
                else
                    nonNegArr[nonNegCount++] = allKeys[i];
            }
            free(allKeys);
            // Построение идеально сбалансированных деревьев из отсортированных массивов
            TreeNode *negTree = NULL, *nonNegTree = NULL;
            if (negCount > 0)
                negTree = build_balanced_tree_from_sorted(negArr, 0, negCount - 1);
            if (nonNegCount > 0)
                nonNegTree = build_balanced_tree_from_sorted(nonNegArr, 0, nonNegCount - 1);
            printf("\nИдеально сбалансированное дерево из отрицательных элементов:\n");
            if (negTree == NULL)
                printf("Нет отрицательных элементов.\n");
            else
                print_tree_top_down(negTree);
            printf("\nИдеально сбалансированное дерево из неотрицательных элементов:\n");
            if (nonNegTree == NULL)
                printf("Нет неотрицательных элементов.\n");
            else
                print_tree_top_down(nonNegTree);
            free(negArr);
            free(nonNegArr);
            free_tree(negTree);
            free_tree(nonNegTree);
        } else if (choice == 0) {
            free_tree(T);
            printf("Выход из программы.\n");
            break;
        } else {
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}
