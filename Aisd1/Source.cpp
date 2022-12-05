#include <stdlib.h>
#include <iostream>
#include "matrix.h"

bool double_control(char* xn);
double double_checker();
bool int_control(char* xn);
int int_checker();

Matrix::Matrix() {
    epsilon = 0;
    rows = 0;
    columns = 0;
    matrix = NULL;
}
Matrix::Matrix(int rows, int columns) {
    if (rows > 0)
        this->rows = rows;
    else throw "Invalid value!";
    if (columns > 0)
        this->columns = columns;
    else throw "Invalid value!";

    matrix = new double* [rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new double[columns];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[i][j] = i + j;
}
int Matrix::GetRows() const {
    return rows;
}
int Matrix::GetCols() const {
    return columns;
}
double Matrix::tr()
{
    double result = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i == j)
            {
                result += matrix[i][j];
            }
        }
    }
    return result;
}
double& Matrix::operator () (int i, int j) {
    if ((i >= 0) && (i < rows) && (j >= 0) && (j < columns))
        return matrix[i][j];
    else throw "Incorrect index values!";
}
Matrix Matrix::operator + (const Matrix& rhs) {
    if ((rows == rhs.rows) && (columns == rhs.columns)) {
        Matrix result(rows, columns);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
        return result;
    }
    throw "The dimensions of the matrices do not match! Addition of matrices with different dimensions is unacceptable!";
}
Matrix Matrix::operator - (const Matrix& rhs) {
    if ((rows == rhs.rows) && (columns == rhs.columns)) {
        Matrix result(rows, columns);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                result.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];
        return result;
    }
    throw "The dimensions of the matrices do not match! Subtraction of matrices with different dimensions is unacceptable!";
}
Matrix Matrix::operator * (const Matrix& rhs) {
    if (columns == rhs.rows) {
        Matrix result(rows, rhs.columns);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < rhs.columns; j++)
                result.matrix[i][j] = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < rhs.columns; j++)
                for (int k = 0; k < columns; k++)
                    result.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
        return result;
    }
    throw "Matrices cannot be multiplied! Invalid dimension!";
}

Matrix Matrix::operator / (const double h) {

    Matrix result(rows, columns);
    if (h == 0)
    {
        std::cout << "invalid syntax, division by zero is not possible";
    }
    else {


        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)

                result.matrix[i][j] = matrix[i][j] / h;
    }
    return result;
}
void Matrix::EnterMatrix() {
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;

    std::cout << "Enter the dimension of the matrix:" << endl;
    std::cout << "Number of rows: ";
    int newRows = int_checker();
    std::cout << "Number of columns: ";
    int newColumns = int_checker();

    Matrix newMatrix(newRows, newColumns);
    for (int i = 0; i < newRows; i++)
        for (int j = 0; j < newColumns; j++) {
            std::cout << "Cell (" << i << ", " << j << ") = ";
            std::cin >> newMatrix.matrix[i][j];
        }

    rows = newRows;
    columns = newColumns;
    matrix = new double* [rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new double[columns];

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[i][j] = newMatrix.matrix[i][j];
}


Matrix Matrix::operator * (const double h) {
    Matrix result(rows, columns);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result.matrix[i][j] = matrix[i][j] * h;
    return result;
}
Matrix operator / (double h, Matrix matrix) {
    Matrix result(matrix.GetRows(), matrix.GetCols());
    if (h == 0)
    {
        std::cout << "invalid syntax, division by zero is not possible";
    }
    else
    {
        result = matrix / h;
        return result;
    }
}
bool Matrix::operator == (const Matrix& rhs) {
    bool result = true;
    if ((rows == rhs.rows) && (columns == rhs.columns)) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                if (abs(matrix[i][j] - rhs.matrix[i][j]) > epsilon)
                {
                    result = false;
                }
    }
    else
    {
        result = false;
    }
    return result;
}
ostream& operator<< (ostream& s, const Matrix& matrix) {

    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.columns; j++)
            s << matrix.matrix[i][j] << " ";
        s << "\n";
    }
    return s;
}

Matrix Matrix::Solution_of_the_equation(const Matrix& vector) {
    double det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) -
        matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
        matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    double invdet = 1 / det;

    Matrix matrix2(3, 3), matrixResult;
    matrix2(0, 0) = (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) * invdet;
    matrix2(0, 1) = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) * invdet;
    matrix2(0, 2) = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) * invdet;
    matrix2(1, 0) = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) * invdet;
    matrix2(1, 2) = (matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2]) * invdet;
    matrix2(1, 1) = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) * invdet;
    matrix2(2, 0) = (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) * invdet;
    matrix2(2, 1) = (matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1]) * invdet;
    matrix2(2, 2) = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) * invdet;

    matrixResult = matrix2 * vector;
    return matrixResult;
}