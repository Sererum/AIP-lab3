#include "matrix.h"

// Конструктор пустой матрицы
Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

// Конструктор единичной матрицы n x n
Matrix::Matrix(int n) : rows(n), cols(n) {
    if (n <= 0) {
        throw std::invalid_argument("Matrix size must be positive.");
    }

    data = new double[n * n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            data[i * n + j] = (i == j) ? 1.0 : 0.0; // Заполняем главную диагональ единицами
        }
    }
}

// Конструктор матрицы m x n с заполнением
Matrix::Matrix(int m, int n, double fill_value) : rows(m), cols(n) {
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive.");
    }

    data = new double[m * n];
    for (int i = 0; i < m * n; ++i) {
        data[i] = fill_value;
    }
}


Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    if (rows > 0 && cols > 0) {
        data = new double[rows * cols];
        for (int i = 0; i < rows * cols; ++i) {
            data[i] = other.data[i];
        }
    } else {
        data = nullptr; 
    }
}

Matrix::~Matrix() {
    delete[] data;
}

double Matrix::get(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Matrix index out of range.");
    }
    return data[i * cols + j];
}

// Сеттер элемента матрицы
void Matrix::set(int i, int j, double value) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Matrix index out of range.");
    }
    data[i * cols + j] = value;
}

// Меняет знак всех элементов матрицы
Matrix Matrix::operator-() const {
	Matrix result(*this);
    for (int i = 0; i < rows * cols; ++i) {
        result.data[i] = -data[i];
    }
	return result;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) { // Защита от самоприсваивания
        if (rows * cols != other.rows * other.cols) {
            delete[] data; // Освобождаем старую память
            data = new double[other.rows * other.cols]; // Выделяем новую память
        }

        rows = other.rows;
        cols = other.cols;

        for (int i = 0; i < rows * cols; ++i) {
        	data[i] = other.data[i];
        }
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
    if (this != &other) { 
        delete[] data; 

        rows = other.rows; 
        cols = other.cols;
		data = other.data;

        other.rows = 0;
        other.cols = 0;
        other.data = nullptr;
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions do not match for addition.");
    }

    for (int i = 0; i < rows * cols; ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions do not match for subtraction.");
    }

    for (int i = 0; i < rows * cols; ++i) {
        data[i] -= other.data[i];
    }
    return *this;
}

Matrix& Matrix::operator*=(double scalar) {
    for (int i = 0; i < rows * cols; ++i) {
        data[i] *= scalar;
    }
    return *this;
}

Matrix& Matrix::operator/=(double scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    for (int i = 0; i < rows * cols; ++i) {
        data[i] /= scalar;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions do not match for addition.");
    }

    Matrix result(*this);
	result += other;

    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions do not match for subtraction.");
    }

    Matrix result(*this);
	result -= other;

    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    }

    Matrix result(rows, other.cols, 0.0); 

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
        	for (int k = 0; k < cols; ++k) {
                result.data[i * other.cols + j] += data[i * cols + k] * other.data[k * other.cols + j];
            }
        }
    }

    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(*this); 
	result *= scalar;

    return result;
}

Matrix Matrix::operator/(double scalar) const {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    Matrix result(*this); 
	result /= scalar;

    return result;
}

ostream& operator<<(ostream& os, const Matrix& matrix) {
	int rows = matrix.rows, cols = matrix.cols;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			os << matrix.data[i * cols + j] << " ";
		}
		os << std::endl;
	}
	return os;
}

Matrix operator*(double scalar, const Matrix& matrix) {
	return matrix * scalar;
}

