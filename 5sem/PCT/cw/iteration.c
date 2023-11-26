#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 3

void swap_rows(float matrix[MATRIX_SIZE][MATRIX_SIZE], int row1, int row2)
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        float temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

float determinant(float matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    float det = 1;

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        // Если текущий элемент на главной диагонали равен нулю,
        // нужно поменять строки местами с ненулевым элементом ниже
        if (matrix[i][i] == 0)
        {
            int j;
            for (j = i + 1; j < MATRIX_SIZE; j++)
            {
                if (matrix[j][i] != 0)
                {
                    swap_rows(matrix, i, j);
                    det *= -1;
                    break;
                }
            }

            // Если не найдено ненулевых элементов, определитель равен нулю
            if (j == MATRIX_SIZE)
            {
                return 0;
            }
        }

        // Приведение матрицы к треугольному виду
        for (int j = i + 1; j < MATRIX_SIZE; j++)
        {
            float ratio = matrix[j][i] / matrix[i][i];
            for (int k = i; k < MATRIX_SIZE; k++)
            {
                matrix[j][k] -= ratio * matrix[i][k];
            }
        }

        det *= matrix[i][i];
    }

    return det;
}

int main()
{
    float matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {12, 12, 1},
        {123, 4, 54},
        {43, 65, 76}};

    float det = determinant(matrix);

    printf("Определитель матрицы: %f\n", det);
}
