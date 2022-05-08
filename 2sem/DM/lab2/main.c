#include "shift.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 30

int main()
{
    int matrix[SIZE][SIZE];
    int tmatrix[SIZE][SIZE];
    int matrixSym[SIZE][SIZE];
    unsigned int n = 0;
    char e;
    char Abeg[SIZE];
    int A[SIZE];
    int maxc = -999999, minc = 999999;

mnz:
    maxc = -999999;
    minc = 999999;

    system("clear");
    printf("Введите элементы множества A\n\n");
    // printf("После каждого неового элемента нажимайте ENTER\n");
    printf("Для прекращения ввода введите q\n\n");
    n = 0;
    int __counter = 1;
    char __ss__[2];
    while (1) {
        printf("Введите №%d элемент множества A: ", __counter);
        scanf("%c", &e);
        if (e == 'q')
            break;
        Abeg[n] = e;
        n++;
        __counter++;
        fgets(__ss__, 2, stdin);
    }

    int cntRight = 0;
    for (int i = 0; i < n; i++) {
        if (isdigit(Abeg[i])) {
            A[cntRight] = Abeg[i] - '0';
            cntRight++;
        }
    }

    for (int i = 0; i < cntRight - 1; i++) {
        for (int j = i + 1; j < cntRight; j++) {
            if (A[i] == A[j])
                cntRight -= shift(A, cntRight, A[i]) - 1;
        }
    }

    buble_sort(A, cntRight);

    // cntRight = maxc - minc + 1;

    printf("Вы ввели множество A\n");
    printf("Множество A - {");
    for (int x = 0; x < cntRight; x++) {
        if (x == cntRight - 1) {
            printf("%d}\n", A[cntRight - 1]);
            break;
        }
        printf("%d, ", A[x]);
    }
    printf("Количество элементов - %d\n", cntRight);

    for (int x = 0; x < cntRight; x++) {
        if (A[x] > maxc)
            maxc = A[x];
        if (A[x] < minc)
            minc = A[x];
    }

    printf("min = %d\n", minc);
    printf("max = %d\n", maxc);

par:
    for (int x = 0; x < SIZE; x++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[x][j] = 0;
        }
    }

    printf("Введите пары\n");
    int cntpair = 1;
    int a, b, tmp;
    int flag = 0;
    for (int x = 0; x < 2000; x++) {
        flag = 0;
        printf("Введите пару №%d, a: ", cntpair);
        scanf("%d", &a);
        for (int i = 0; i < cntRight; i++) {
            if (A[i] == a) {
                flag = 1;
                break;
            }
        }
        if (!flag)
            continue;
        tmp = a;
        if (tmp == 'q') {
            a = 0;
            break;
        }
        printf("");
        printf("Введите пару №%d, b: ", cntpair);
        scanf("%d", &b);
        for (int i = 0; i < cntRight; i++) {
            if (A[i] == b) {
                flag = 1;
                break;
            }
        }
        if (!flag)
            continue;
        tmp = b;
        if (tmp == 'q') {
            b = 0;
            break;
        }
        matrix[a - minc][b - minc] = 1;
        cntpair++;
    }

    system("clear");
    printf("\n");
    system("clear");

    printf("[!] Ваша матрица [!]\n\n");
    for (int x = 0; x < cntRight; x++) {
        for (int j = 0; j < cntRight; j++) {
            printf("%d ", matrix[x][j]);
        }
        printf("\n");
    }

    /* рефлексивность */
    int ref = 1;
    for (int i = 0; i < cntRight; i++) {
        for (int j = 0; j < cntRight; j++) {
            if (i == j && !matrix[i][j]) {
                ref = 0;
                break;
            }
        }
    }

    printf("\n");
    printf("[!] Свойства [!]\n");
    if (ref)
        printf("1. Рефлексивно\n");
    else
        printf("1. Не рефлексивно\n");

    /* симметричность */
    // int matrixSym[cntRight][cntRight];
    int sym = 0;
    for (int i = 0; i < cntRight; i++) {
        for (int j = 0; j < cntRight; j++) {
            matrixSym[j][i] = matrix[i][j];
        }
    }

    for (int i = 0; i < cntRight; i++)
        for (int j = 0; j < cntRight; j++)
            if (matrixSym[i][j] == matrix[i][j])
                sym = 1;
            else {
                sym = 0;
                break;
            }

    if (sym)
        printf("2 - Симметрично\n");
    else
        printf("2 - Не симметрично\n");

    /* антисимметричность */
    int antsym = 1;
    for (int i = 0; i < cntRight; i++) {
        for (int j = 0; j < cntRight; j++) {
            if (i != j && matrix[i][j]) {
                antsym = 0;
                break;
            }
        }
    }

    if (antsym)
        printf("3 - Антисимметрично\n");
    else
        printf("3 - Не антисимметрично\n");

    // for (int i = 0; i < cntRight; i++) {
    //     for (int j = 0; j < cntRight; j++) {
    //         printf("%d ", matrixSym[j][i]);
    //     }
    //     printf("\n");
    // }

    /* транзитивность */
    int trz = 1;
    for (int i = 0; i < cntRight; i++)
        for (int j = 0; j < cntRight; j++) {
            tmatrix[i][j] = 0;
            for (int k = 0; k < n; k++) {
                tmatrix[i][j] += matrix[i][k] && matrix[k][j];
                if (tmatrix[i][j])
                    tmatrix[i][j] = 1;
            }
        }

    for (int i = 0; i < cntRight; i++) {
        for (int j = 0; j < cntRight; j++) {
            if (matrix[i][j] != tmatrix[i][j]) {
                trz = 0;
                break;
            }
        }
    }

    if (trz)
        printf("4 - Транзитивно\n");
    else
        printf("4 - Не транзитивно\n");

    printf("\n");

    // for (int i = 0; i < cntRight; i++) {
    //     for (int j = 0; j < cntRight; j++) {
    //         printf("%d ", tmatrix[j][i]);
    //     }
    //     printf("\n");
    // }

    printf("[!] Действия [!]\n");
    printf("1 - Ввести множество заново.\n");
    printf("2 - Ввести пары заново.\n");
    printf("3 - Завершить работу.\n");
    printf("\n");

    char sssss[2];
    fgets(sssss, 2, stdin);
    int knk;
    printf("Выберите пункт: ");
    scanf("%d", &knk);

    switch (knk) {
    case 1:
        system("clear");
        fgets(__ss__, 2, stdin);
        goto mnz;

    case 2:
        system("clear");
        fgets(__ss__, 2, stdin);
        goto par;

    case 3:
        return 0;

    default:
        printf("Введен неизвестный символ.\n Завершение программы.\n");
        return 0;
    }
}