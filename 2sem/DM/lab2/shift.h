void swap(int *a, int *b) {
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return;
}

int shift(int *array, int N, int count) {
    int i;
    int nn = 0;

    for (i = 0; i < N - 1; i++) {
        if (array[i] == count && array[i] != array[i + 1]) {
            swap(&array[i], &array[i + 1]);
            i = 0;
        }
        if (array[N - 1] == count) {
            N--;
            nn++;
        }
    }
    return nn;
}

void buble_sort(int *array, int N) {
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
