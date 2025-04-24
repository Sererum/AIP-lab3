#pragma once

#include "libs.h"

class MyString {
private:
    char* data;   // Указатель на динамически выделенную память
    int length; // Длина строки без завершающего нуля

public:
    // Конструкторы
    MyString(); // Пустая строка
    MyString(const char* str); // Строка из C-строки
	MyString(int length, char fill_char);
	MyString(const MyString &str);
    MyString(MyString&& other);

	MyString& operator=(const MyString &str);
    MyString& operator=(MyString&& other);

    // Деструктор
    ~MyString();

    // Методы
    char get(int i) const;
    void set(int i, char c);
    void set_new_string(const char* str);
    void print(const char *end="\n") const;
    void read_line();
	void read_line2();

    // Геттер длины строки
    int get_length() const { return length; }
	
	MyString operator+(const MyString& other) const;
    MyString& operator+=(const MyString& other);

	bool operator==(const MyString& other) const;
	bool operator!=(const MyString& other) const;
	bool operator<(const MyString& other) const;
	bool operator<=(const MyString& other) const;
	bool operator>(const MyString& other) const;
	bool operator>=(const MyString& other) const;

	friend ostream& operator<<(ostream& os, const MyString& str);
	friend istream& operator>>(istream& is, MyString& str);

    char& operator[](int i); // Для неконстантных объектов
    const char& operator[](int i) const; // Для константных объектов
};

MyString operator+(const char* first, const MyString& second); 

bool operator==(const char* first, const MyString& second); 
bool operator!=(const char* first, const MyString& second); 
bool operator<(const char* first, const MyString& second); 
bool operator<=(const char* first, const MyString& second); 
bool operator>(const char* first, const MyString& second); 
bool operator>=(const char* first, const MyString& second); 

