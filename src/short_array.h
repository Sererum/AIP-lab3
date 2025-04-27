#pragma once

#include "libs.h"

#define MAX_LOC_SIZE 11
#define MIN_DYN_CAPAC 16
#define IS_LOCAL 1
#define IS_DYNAMIC 0

union ShortArray {
private:
	struct {
		short array[MAX_LOC_SIZE];
		size_t size : 15;
		size_t is_local : 1;
	} local;

	struct {
		size_t size;
		size_t capacity;
		short* array;
	} dynamic;

    void resize_local(size_t new_size, short fill_value = 0);
    void resize_dynamic(size_t new_size, short fill_value = 0);

public:
	ShortArray();
    ShortArray(size_t initial_size, short fill_value = 0);
    ShortArray(const ShortArray& other);
    ShortArray(ShortArray&& other);

    ShortArray& operator=(const ShortArray& other);
    ShortArray& operator=(ShortArray&& other);

    ~ShortArray();

	bool is_local() const { return local.is_local; }
	bool is_dynamic() const { return !local.is_local; }

    void push(short new_val);
    short pop();
    size_t size() const { return local.is_local ? local.size : dynamic.size; }
    void resize(size_t new_size, short fill_value = 0);

    short& operator[](size_t index);
    const short& operator[](size_t index) const;
};
