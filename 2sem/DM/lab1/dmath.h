#include <ctype.h>
#include <malloc.h>
#define CAPASITY_NORMAL 50

typedef struct {
    char *pointer;
    int size;
    int capacity;
} IntVector;

void buble_sort(char *array, int N) {
    int i, j, temp;

    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            if (array[i] > array[j]) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int str_to_int(char *str) {
    int step = 0;
    int count = 0;

    while (!(isdigit(str[step]))) {
        if (step >= strlen(str)) return -999;
        step++;
    }

    for (int i = step; i < strlen(str); i++) {
        switch (str[i]) {
            case '0':
            count *= 10;
            count += 0;
            break;
            
            case '1':
            count *= 10;
            count += 1;
            break;
            
            case '2':
            count *= 10;
            count += 2;
            break;

            case '3':
            count *= 10;
            count += 3;
            break;

            case '4':
            count *= 10;
            count += 4;
            break;

            case '5':
            count *= 10;
            count += 5;
            break;

            case '6':
            count *= 10;
            count += 6;
            break;

            case '7':
            count *= 10;
            count += 7;
            break;

            case '8':
            count *= 10;
            count += 8;
            break;

            case '9':
            count *= 10;
            count += 0;
            break;
        
            default:
            break;
        }
    }

    return count;
}

void print_array(char *array, int size) {
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("%c", array[i]);
        if (i < size - 1) printf(", ");
    }
    printf("}");
    printf("\n");
}

void print_sets(char *array1, int N1, char *array2, int N2) {
    printf("A = ");
    print_array(array1, N1);
    printf("B = ");
    print_array(array2, N2);
}

void print_set(char *array, int size) {
    printf("{");
    for (int i = 0; i < size; i++) {
        printf("%c", array[i]);
        if (i < size - 1) printf(", ");
    }
    printf("}");
}

IntVector *int_vector_new(size_t initial_capacity) {
    IntVector *array;

    array = (IntVector *)malloc(sizeof(IntVector));
    if (array == NULL)
        return NULL;

    array->size = 0;
    array->capacity = initial_capacity;
    array->pointer = (char *)malloc(initial_capacity * sizeof(int));
    if (array->pointer == NULL)
        return NULL;

    return array;
}

void int_vector_set_item(IntVector *v, size_t index, int item) {
    v->pointer[index] = item;
    
    if (index < v->capacity)
        v->size++;
}

int int_vector_push_back(IntVector *v, int item) {
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        v->pointer = realloc(v->pointer, v->capacity * sizeof(int));
        if (v->pointer == NULL)
            return -1;

        int_vector_set_item(v, v->size, item);
    }
    else {
        int_vector_set_item(v, v->size, item);
    }

    if (v->pointer[v->size - 1] != item || v->pointer == NULL)
        return -1;
    else
        return 0;
}

void int_vector_pop_back(IntVector *v) {
    if (v->size <= 0)
        return;
    else {
        v->pointer[v->size - 1] = 0;
        v->size--;
    }
}

int int_vector_shrink_to_fit(IntVector *v) {
    if (v->capacity == v->size)
        return 0;
    else {
        v->capacity = v->size;
        v->pointer = realloc(v->pointer, v->capacity * sizeof(int));
            if (v->pointer == NULL)
                return -1;
    }

    if (v->capacity != v->size || v->pointer == NULL)
        return -1;
    else
        return 0;
}

void int_vector_free(IntVector *v) {
    free(v->pointer);
    free(v);
}

void int_vector_delete_copy(IntVector *v) {
    int i, j, k;

    for (i = 0; i < v->size; i++) {
        for (j = i + 1; j < v->size; j++) {
            if (v->pointer[i] == v->pointer[j]) {
                for (k = j; k < v->size - 1; k++) {
                    v->pointer[k] = v->pointer[k + 1];
                }
                int_vector_pop_back(v);
            }
        }
    }
}

int issubset(IntVector *A, IntVector *B, char firstSet, char secondSet) {
    int i, j;
    int flag[A->size];

    for (i = 0; i < B->size; i++) {
        if (B->pointer[i] == firstSet) return 1;
    }

    for (i = 0; i < A->size; i++) {
        flag[i] = 0;
    }

    for (i = 0; i < A->size; i++) {
        for (j = 0; j < B->size; j++) {
            if (A->pointer[i] == B->pointer[j]) {
                flag[i] = 1;
            }
        }
    }

    for (i = 0; i < A->size; i++) {
        if (!(flag[i])) return 0;
    }

    return 1;
}

void unification(IntVector *A, IntVector *B, IntVector *Result) {
    int i, j;

    Result->size = A->size + B->size;

    for (i = 0; i < A->size; i++) {
        Result->pointer[i] = A->pointer[i]; 
    }

    for (j = i, i = 0; j < Result->size; j++, i++) {
        Result->pointer[j] = B->pointer[i];
    }

    int_vector_delete_copy(Result);
}

void intersection(IntVector *A, IntVector *B, IntVector *Result) {
    int i, j, k = 0;

    for (i = 0; i < A->size; i++) {
        for (j = 0; j < B->size; j++) {
            if (A->pointer[i] == B->pointer[j]) {
                Result->size += 1;
                Result->pointer[k] = A->pointer[i];
                k++;
            }
        } 
    }

    int_vector_delete_copy(Result);

    int_vector_shrink_to_fit(Result);
}

void difference(IntVector *A, IntVector *B, IntVector *Result) {
    int i, j, k = 0;
    int flag;

    for (i = 0; i < A->size; i++) {
        flag = 1;
        for (j = 0; j < B->size; j++) {
            if (A->pointer[i] == B->pointer[j]) flag = 0;
        }
        if (flag) {
            Result->size += 1;
            Result->pointer[k] = A->pointer[i];
            k++;
        }
    }

    int_vector_delete_copy(Result);

    int_vector_shrink_to_fit(Result);
}

void shift(IntVector *v, char count) {
    char temp;
    int flag = 0;
    for (int i = 0; i < v->size; i++) {
        if (v->pointer[i] == count && i < v->size - 1) {
            temp = v->pointer[i];
            v->pointer[i] = v->pointer[i + 1];
            v->pointer[i + 1] = temp;
            flag = 1;
        }
    }
    if (flag) int_vector_pop_back(v);
}

void symmetric_difference(IntVector *A, IntVector *B, IntVector *Result) {
    IntVector *I;
    IntVector *U;

    I = int_vector_new(CAPASITY_NORMAL);
    U = int_vector_new(CAPASITY_NORMAL);

    unification(A, B, U);
    intersection(A, B, I);
    difference(U, I, Result);

    int_vector_free(I);
    int_vector_free(U);
}