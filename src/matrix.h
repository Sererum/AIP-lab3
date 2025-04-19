#pragma once

#include "libs.h" 

class Matrix {
private:
    int rows;       // Количество строк
    int cols;       // Количество столбцов
    double* data;   // Указатель на массив элементов матрицы

public:
    // Конструкторы
    Matrix(); // Пустая матрица
    Matrix(int n); // Единичная матрица n x n
    Matrix(int m, int n, double fill_value = 0); // Матрица m x n с заполнением
    Matrix(const Matrix& other); // Конструктор копирования
    Matrix(Matrix&& other);

    // Деструктор
    ~Matrix();

    // Геттеры
    double get(int i, int j) const;
    int get_height() const { return rows; }
    int get_width() const { return cols; }
	bool is_empty() const { return rows == 0 || cols == 0; };

    // Сеттеры
    void set(int i, int j, double value);

    // Операторы
    Matrix& operator=(const Matrix& other); // Оператор присваивания
    Matrix& operator=(Matrix&& other);

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

	//scalar — это просто переменная типа double, которая используется для выполнения арифметических операций (умножение или деление) с матрицей
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    Matrix operator-() const;

	friend ostream& operator<<(ostream& os, const Matrix& matrix);

	friend Matrix operator*(double scalar, const Matrix& matrix);
};

