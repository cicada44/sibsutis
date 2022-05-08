#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dmath.h"

int main() {
    IntVector *A;
    IntVector *B;
    int number = 1;
    char c[10];
    int bmenu;

    IntVector *Result;


    /* Change A and B */
    while (0) {
        changeAB:
        printf("Ввод множеств повторно\n");
        fgets(c, 10, stdin);
        int_vector_free(A);
        int_vector_free(B);
    }

    /* read(A) */
    {
        A = int_vector_new(CAPASITY_NORMAL);

        printf("!!! ПРОГРАММА РАБОТАЕТ С СИМВОЛАМИ ЛАТИНСКОГО АЛФАВИТА !!!\n\n");
        printf("CTRL+Z - выход из программы\n\n\n");
        printf("ENTER НА СТАДИИ ВВОДА - ОКОНЧАНИЕ ВВОДА\n\n\n");

        while (1) {
            printf("%d элемент 1-ого мн-ва: ", number);
            fgets(c, 10, stdin);
            if (!((c[0] >= 'a' && c[0] <= 'z') || (c[0] >= 'A' && c[0] <= 'Z'))) {
                number = 1;
                break;
            }
            else int_vector_push_back(A, c[0]);
            number++;
        }

        int_vector_delete_copy(A);
    }

    /* read(B) */
    {
        B = int_vector_new(CAPASITY_NORMAL);

        while (1) {
            printf("%d элемент 2-ого мн-ва: ", number);
            fgets(c, 10, stdin);
            if (!((c[0] >= 'a' && c[0] <= 'z') || (c[0] >= 'A' && c[0] <= 'Z'))) {
                number = 1;
                break;
            }
            else int_vector_push_back(B, c[0]);
            number++;
        }

        int_vector_delete_copy(B);
    }

    /* Menu */
    menu:
    {
        buble_sort(A->pointer, A->size);
        buble_sort(B->pointer, B->size);
        printf("Множества:\n");
        print_sets(A->pointer, A->size, B->pointer, B->size);
        printf("Введите номер действия соответственно желаемому:\n");
        printf("1 - A ⊆ B (Является подмножеством)\n");
        printf("2 - B ⊆ A \n");
        printf("3 - A ⋃ B (Обьединение)\n");
        printf("4 - A ⋂ B (Пересечение)\n");
        printf("5 - A \\ B (Разность)\n");
        printf("6 - B \\ A\n");
        printf("7 - A ∆ B (Исключающее и - XOR)\n");
        printf("8 - Режим изменения множеств\n");
        printf("9 - Выйти из программы\n");
        printf("Ввод ---> ");
        scanf("%d", &bmenu);

        switch (bmenu) {
        case 1:
            printf("Для множеств:\n");
            print_sets(A->pointer, A->size, B->pointer, B->size);
            if (issubset(A, B, 'A', 'B')) {
                printf("A является подмножеством B.\n");
            }
            else printf("A не является подмножеством B.\n");
            printf("Нажмите ENTER для продолжения\n");
            fgets(c, 10, stdin);
            fgets(c, 10, stdin);
            break;
        
        case 2:
            printf("Для множеств:\n");
            print_sets(A->pointer, A->size, B->pointer, B->size);
            if (issubset(B, A, 'B', 'A')) {
                printf("B является подмножеством A\n");
            }
            else printf("B не явялется подмножеством A\n");
            printf("Нажмите ENTER для продолжения\n");
            fgets(c, 10, stdin);
            fgets(c, 10, stdin);
            break;

        case 3:
            Result = int_vector_new(CAPASITY_NORMAL);
            unification(A, B, Result);
            buble_sort(Result->pointer, Result->size);
            printf("A ⋃ B = ");
            print_set(A->pointer, A->size);
            printf(" ⋃ ");
            print_set(B->pointer, B->size);
            printf(" = ");
            print_array(Result->pointer, Result->size);
            printf("Нажмите ENTER для продолжения\n");
            fgets(c, 10, stdin);
            fgets(c, 10, stdin);
            break;
        
        case 4:
            Result = int_vector_new(CAPASITY_NORMAL);
            intersection(A, B, Result);
            buble_sort(Result->pointer, Result->size);
            printf("A ⋂ B = ");
            print_set(A->pointer, A->size);
            printf(" ⋂ ");
            print_set(B->pointer, B->size);
            printf(" = ");
            print_array(Result->pointer, Result->size);
            printf("Нажмите ENTER для продолжения\n");
            fgets(c, 10, stdin);
            fgets(c, 10, stdin);
            break;

        case 5:
            Result = int_vector_new(CAPASITY_NORMAL);
            difference(A, B, Result);
            buble_sort(Result->pointer, Result->size);
            printf("A \\ B = ");
            print_set(A->pointer, A->size);
            printf(" \\ ");
            print_set(B->pointer, B->size);
            printf(" = ");
            print_array(Result->pointer, Result->size);
            printf("Нажмите ENTER для продолжения\n");
            fgets(c, 10, stdin);
            fgets(c, 10, stdin);
            break;

        case 6:
            Result = int_vector_new(CAPASITY_NORMAL);
            difference(B, A, Result);
            buble_sort(Result->pointer, Result->size);
            printf("B \\ A = ");
            print_set(B->pointer, B->size);
            printf(" \\ ");
            print_set(A->pointer, A->size);
            printf(" = ");
            print_array(Result->pointer, Result->size);
            printf("Нажмите ENTER для продолжения\n");
            fgets(c, 10, stdin);
            fgets(c, 10, stdin);
            break;

        case 7:
            Result = int_vector_new(CAPASITY_NORMAL);
            symmetric_difference(A, B, Result);
            buble_sort(Result->pointer, Result->size);
            printf("A ∆ B = ");
            print_set(A->pointer, A->size);
            printf(" ∆ ");
            print_set(B->pointer, B->size);
            printf(" = ");
            print_array(Result->pointer, Result->size);
            printf("Нажмите ENTER для продолжения\n");
            fgets(c, 10, stdin);
            fgets(c, 10, stdin);
            break;

        case 8:
            goto changeAB;
            break;
        
        case 9:
            goto endprog;
            break;

        default:
            printf("Введён неопознанный символ\n");
            goto endprog;
            break;
        }
    }

    goto menu;

    endprog: 
    return 0;
    
}