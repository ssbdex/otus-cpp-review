#include "matrix.h"

#include <iostream>
#include <cassert>
#include <iomanip>

using namespace mymatrix;

/**
 * Example from 05_homework.pdf
 */
void example() {
    // бесконечная матрица int заполнена значениями -1
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0); // все ячейки свободны
    [[maybe_unused]] auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    
    /*  Плохой "сайд эффект", но не придумал, как его избежать.?!
        auto b = matrix[0][0];
        b=34;
        assert(matrix[0][0]==34); //true, but expected false by semantic
    */
    matrix[100][100] = 314;

    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    for (auto c : matrix)
    {
        unsigned x;
        unsigned y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
}


template<typename T, T defval>
void printMatrix(Matrix<T, defval>& m, unsigned x1, unsigned y1, unsigned x2, unsigned y2) {
    for (auto x = x1; x <= x2; x++) {
        for (auto y = y1; y <= y2; y++) {
            std::cout << std::setw(5) << m[x][y];
        }
        std::cout << std::endl;
    }
}

/**
    Вывод с cout всех занятых элементов матрицы m
*/
template<typename T, T defval>
void printMatrixElements(Matrix<T, defval>& m) {
    for (auto c : m) {
        unsigned x;
        unsigned y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << "[" << x << "," << y << "] = " << v << std::endl;
    }
}

int main(int, char**) {

    example();

    // При запуске программы необходимо создать матрицу с пустым значением 0, заполнить главную
    // диагональ матрицы (от [0,0] до [9,9]) значениями от 0 до 9.
    // Второстепенную диагональ (от [0,9] до [9,0]) значениями от 9 до 0
    Matrix<int, 0> m;
    const int SIZE = 10;
    for (int i = 0; i < SIZE; i++) {
        m[i][i] = i;
        m[i][SIZE - 1 - i] = SIZE - 1 - i;
    }

    // Необходимо вывести фрагмент матрицы от [1,1] до [8,8]. Между столбцами пробел. Каждая строка
    // матрицы на новой строке консоли.
    printMatrix(m, 1, 1, 8, 8);

    // Вывести количество занятых ячеек.
    std::cout << m.size() << std::endl;

    // Вывести все занятые ячейки вместе со своими позициями.
    printMatrixElements(m);

    // Опционально реализовать каноническую форму оператора `=`, допускающую выражения
   // ((matrix[100][100] = 314) = 0) = 217
    ((m[100][100] = 314) = 0) = 217;
    std::cout << m[100][100];

    return 0;
}