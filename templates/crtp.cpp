#include <iostream>
#include <vector>
#include <type_traits>

// Простой пример CRTP
template <typename T>
class Base {
    public:
    void interface() {
        static_cast<T*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
    public:
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};

// ========== Реализация Matrix через CRTP ==========

// Базовый класс для всех матриц
template <typename Derived, typename T, size_t Rows, size_t Cols>
class MatrixBase {
public:
    T& operator()(size_t row, size_t col) {
        return static_cast<Derived*>(this)->getData()[row * Cols + col];
    }
    
    const T& operator()(size_t row, size_t col) const {
        return static_cast<const Derived*>(this)->getData()[row * Cols + col];
    }
    
    size_t rows() const { return Rows; }
    size_t cols() const { return Cols; }
    
    void print() const {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                std::cout << (*static_cast<const Derived*>(this))(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

// CRTP класс, добавляющий метод trace только для квадратных матриц
template <typename Derived, typename T, size_t Size>
class SquareMatrixMixin {
public:
    T trace() const {
        T sum{};
        for (size_t i = 0; i < Size; ++i) {
            sum += static_cast<const Derived*>(this)->operator()(i, i);
        }
        return sum;
    }
};

// Пустой класс для не-квадратных матриц (ничего не добавляет)
template <typename Derived, typename T, size_t Rows, size_t Cols>
class NonSquareMatrixMixin {};

// Класс Matrix с условным наследованием от SquareMatrixMixin
template <typename T, size_t Rows, size_t Cols>
class Matrix : public MatrixBase<Matrix<T, Rows, Cols>, T, Rows, Cols>,
               public std::conditional<Rows == Cols,
                                       SquareMatrixMixin<Matrix<T, Rows, Cols>, T, Rows>,
                                       NonSquareMatrixMixin<Matrix<T, Rows, Cols>, T, Rows, Cols>>::type {
private:
    std::vector<T> data;
    
public:
    Matrix() : data(Rows * Cols, T{}) {}
    
    Matrix(std::initializer_list<T> values) : data(values) {
        data.resize(Rows * Cols, T{});
    }
    
    std::vector<T>& getData() { return data; }
    const std::vector<T>& getData() const { return data; }
};

int main() {
    std::cout << "=== Простой пример CRTP ===" << std::endl;
    Derived derived;
    derived.interface();
    
    std::cout << "\n=== Пример с Matrix ===" << std::endl;
    
    // Квадратная матрица 3x3 с типом double
    Matrix<double, 3, 3> squareMatrix{1.0, 2.0, 3.0,
                                       4.0, 5.0, 6.0,
                                       7.0, 8.0, 9.0};
    
    std::cout << "Square matrix 3x3 (double):" << std::endl;
    squareMatrix.print();
    std::cout << "Trace: " << squareMatrix.trace() << std::endl; // Доступен!
    
    // Квадратная матрица 2x2 с типом int
    Matrix<int, 2, 2> intMatrix{1, 2,
                                 3, 4};
    
    std::cout << "\nSquare matrix 2x2 (int):" << std::endl;
    intMatrix.print();
    std::cout << "Trace: " << intMatrix.trace() << std::endl; // Доступен!
    
    // Прямоугольная матрица 2x3 с типом double
    Matrix<double, 2, 3> rectMatrix{1.0, 2.0, 3.0,
                                      4.0, 5.0, 6.0};
    
    std::cout << "\nRectangular matrix 2x3 (double):" << std::endl;
    rectMatrix.print();
    // Если раскомментировать следующую строку, получим ошибку компиляции:
    // rectMatrix.trace(); // ОШИБКА: нет члена 'trace' в 'Matrix<double, 2, 3>'
    
    return 0;
}