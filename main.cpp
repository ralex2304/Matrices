#include <stdio.h>

const int FIELD_WIDTH = 3;

enum class MatrixType {
    RECT      =  0,
    TRI_UP    =  1,
    TRI_DOWN  =  2,
};

struct Matrix {
    MatrixType type;
    size_t height;
    size_t width;

    int array[20];
};

void print_matrix(const Matrix matrix);
Matrix multiple_matrices(const Matrix matrix1, const Matrix matrix2);

int main() {
    static Matrix matrices[] = {
        {
            MatrixType::RECT, 3, 4,
            {
                1,  2,  3,  4,
                5,  6,  7,  8,
                9, 10, 11, 12
            }
        }, {
            MatrixType::RECT, 4, 2,
            {
                1,  2,
                3,  4,
                5,  6,
                7,  8
            }
        }, {
            MatrixType::TRI_UP, 4, 4,
            {
                1,  2,  3,  4,
                    5,  6,  7,
                        8,  9,
                           10
            }
        }, {
            MatrixType::TRI_DOWN, 4, 4,
            {
                1,
                2,  3,
                4,  5,  6,
                7,  8,  9, 10
            }
        }
    };

    for (size_t i = 0; i < sizeof(matrices) / sizeof(Matrix); i++){
        printf("Matrix %zu:\n", i + 1);
        print_matrix(matrices[i]);
    }

    printf("Multiplied matrix:\n");
    print_matrix(multiple_matrices(matrices[0], matrices[1]));
}

void print_matrix(const Matrix matrix) {
    switch (matrix.type)
    {
    case MatrixType::RECT:
        for (size_t i = 0; i < matrix.height; i++) {

            for (size_t j = 0; j < matrix.width; j++)
                printf("%*d ", FIELD_WIDTH, matrix.array[matrix.width * i + j]);

            putchar('\n');
        }
        break;
    case MatrixType::TRI_UP:
        for (size_t i = 0; i < matrix.height; i++) {

            for (size_t j = 0; j < i; j++)
                for (size_t k = 0; k < FIELD_WIDTH + 1; k++)
                    putchar(' ');

            for (size_t j = i; j < matrix.width; j++)
                printf("%*d ", FIELD_WIDTH, matrix.array[matrix.width * i - (i * (i + 1) / 2) + j]);

            putchar('\n');
        }
        break;
    case MatrixType::TRI_DOWN:
        for (size_t i = 0; i < matrix.height; i++) {

            for (size_t j = 0; j < i + 1; j++)
                printf("%*d ", FIELD_WIDTH, matrix.array[(i * (i + 1) / 2) + j]);

            putchar('\n');
        }
        break;
    default:
        break;
    }
}

Matrix multiple_matrices(const Matrix matrix1, const Matrix matrix2) {
    if (matrix1.type != MatrixType::RECT || matrix2.type != MatrixType::RECT) {
        printf("Can't multiple non rect matrices\n");
        return matrix1;
    }

    if (matrix1.width != matrix2.height) {
        printf("Can't multiple matrices %zux%zu and %zu x%zu\n",
               matrix1.height, matrix1.width, matrix2.height, matrix2.width);
        return matrix1;
    }

    Matrix result = {MatrixType::RECT, matrix1.height, matrix2.width, {0}};

    for (size_t i = 0; i < result.height; i++) {
        for (size_t j = 0; j < result.width; j++) {
            result.array[result.width * i + j] = 0;
            for (size_t k = 0; k < matrix1.width; k++) {
                result.array[result.width * i + j] +=
                        matrix1.array[i * matrix1.width + k] * matrix2.array[k * matrix2.width + j];
            }
        }
    }

    return result;
}
