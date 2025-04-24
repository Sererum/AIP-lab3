#pragma once

#inclue "libs.h"

union ShortArray {
private:
	struct {
		short array[11];
		size_t size : 15;
		size_t is_dynamic : 1;
	} local;

	struct {
		size_t size;
		size_t capacity;
		short* array;
	} dynamic;

public:
	ShortArray();
    ShortArray(size_t initial_size, short fill_value = 0);
    ShortArray(const ShortArray& other);
    ShortArray(ShortArray&& other);

    ShortArray& operator=(const ShortArray& other);
    ShortArray& operator=(ShortArray&& other);

    ~ShortArray();

    void push(short new_val);
    short pop();
    size_t size() const { return count; }
    void resize(size_t new_size, short fill_value = 0);

    short& operator[](size_t index);
    const short& operator[](size_t index) const;
};
