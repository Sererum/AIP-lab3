#include "short_array.h"

ShortArray::ShortArray() {
    local.size = 0;
    local.is_local = IS_LOCAL;
}

ShortArray::ShortArray(size_t initial_size, short fill_value) {
    if (initial_size <= MAX_LOC_SIZE) {
        local.size = initial_size;
        local.is_local = IS_LOCAL;
        std::fill(local.array, local.array + initial_size, fill_value);
    } else {
        dynamic.size = initial_size;
        dynamic.capacity = initial_size;
        dynamic.array = new short[initial_size];
        std::fill(dynamic.array, dynamic.array + initial_size, fill_value);
    }
}

ShortArray::ShortArray(const ShortArray& other) {
	*this = other;
}

ShortArray::ShortArray(ShortArray&& other) {
	*this = std::move(other);
}

ShortArray& ShortArray::operator=(const ShortArray& other) {
    if (this == &other) {
        return *this;
    }

    if (is_dynamic()) {
        delete[] dynamic.array;
    }

    if (other.is_local()) {
        std::copy(other.local.array, other.local.array + other.local.size, local.array);
        local.size = other.local.size;
        local.is_local = IS_LOCAL;
    } else {
        dynamic.size = other.dynamic.size;
        dynamic.capacity = other.dynamic.capacity;
        dynamic.array = new short[dynamic.capacity];
        std::copy(other.dynamic.array, other.dynamic.array + dynamic.size, dynamic.array);
    }

    return *this;
}

ShortArray& ShortArray::operator=(ShortArray&& other) {
    if (this == &other) {
        return *this;
    }

    if (is_dynamic()) {
        delete[] dynamic.array;
    }

    if (other.is_dynamic()) {
        dynamic.size = other.dynamic.size;
        dynamic.capacity = other.dynamic.capacity;
        dynamic.array = other.dynamic.array;
        other.dynamic.array = nullptr;
    } else {
        std::copy(other.local.array, other.local.array + other.local.size, local.array);
        local.size = other.local.size;
        local.is_local = IS_LOCAL;
    }

    other.local.size = 0;
    other.local.is_local = IS_LOCAL;

    return *this;
}

ShortArray::~ShortArray() {
    if (is_dynamic()) {
        delete[] dynamic.array;
    }
}

void ShortArray::push(short new_val) {
    if (is_local() && local.size < MAX_LOC_SIZE) {
        local.array[local.size++] = new_val;
		return;
    } 

	if (is_local()) {
		int size = local.size;
		short copy_array[MAX_LOC_SIZE];
		std::copy(local.array, local.array + local.size, copy_array);

		dynamic.size = size;
		dynamic.capacity = MIN_DYN_CAPAC;
		dynamic.array = new short[dynamic.capacity];
		std::copy(copy_array, copy_array + size, dynamic.array);
	} else if (dynamic.size == dynamic.capacity) {
		dynamic.capacity *= 2;
		short* new_array = new short[dynamic.capacity];
		std::copy(dynamic.array, dynamic.array + dynamic.size, new_array);
		delete[] dynamic.array;
		dynamic.array = new_array;
	}
	dynamic.array[dynamic.size++] = new_val;
}

short ShortArray::pop() {
	
	if (is_local()) {
        if (local.size == 0) {
            throw std::out_of_range("Array is empty");
        }
        return local.array[--local.size];
	}


	if (dynamic.size == 0)
		throw std::out_of_range("Array is empty");
	
	short pop_value = dynamic.array[--dynamic.size];
	if (dynamic.size == MAX_LOC_SIZE) {

		short copy_array[MAX_LOC_SIZE];
		std::copy(dynamic.array, dynamic.array + MAX_LOC_SIZE, copy_array);
		delete[] dynamic.array;

		std::copy(copy_array, copy_array + MAX_LOC_SIZE, local.array);
		local.size = MAX_LOC_SIZE;
		local.is_local = IS_LOCAL;
	}
	return pop_value;
}

void ShortArray::resize(size_t new_size, short fill_value) {
	if (is_local())
		resize_local(new_size, fill_value);
	else
		resize_dynamic(new_size, fill_value);
}

void ShortArray::resize_local(size_t new_size, short fill_value) {
	if (new_size <= MAX_LOC_SIZE) {
		if (new_size > local.size)
			std::fill(local.array + local.size, local.array + new_size, fill_value); 

		local.size = new_size;
		return; 
	}

	short cur_array[MAX_LOC_SIZE];
	std::copy(local.array, local.array + local.size, cur_array);

	short *new_array = new short[new_size];
	std::copy(cur_array, cur_array + local.size, new_array);

	std::fill(new_array + local.size, new_array + new_size, fill_value);

	dynamic.array = new_array;
	dynamic.size = new_size;
	dynamic.capacity = new_size;
}

void ShortArray::resize_dynamic(size_t new_size, short fill_value) {

	// new_size <= 11
	if (new_size <= MAX_LOC_SIZE) {
		short copy_array[new_size];
		std::copy(dynamic.array, dynamic.array + new_size, copy_array);
		delete[] dynamic.array;

		std::copy(copy_array, copy_array + new_size, local.array);
		local.size = new_size;
		local.is_local = IS_LOCAL;
		return;
	}

	// 11 < new_size <= size
	if (new_size <= dynamic.size) {
		dynamic.size = new_size;
		return;
	}

	// new_size > capacity 
	if (new_size > dynamic.capacity) {
		short *new_array = new short[new_size];
		std::copy(dynamic.array, dynamic.array + dynamic.size, new_array);
		std::fill(new_array + dynamic.size, new_array + new_size, fill_value);
		delete[] dynamic.array;

		dynamic.array = new_array;
		dynamic.capacity = new_size;
		dynamic.size = new_size;
		return;
	}	

	// size < new_size <= capacity
	std::fill(dynamic.array + dynamic.size, dynamic.array + new_size, fill_value);
}

short& ShortArray::operator[](size_t index) {
    if ((is_dynamic() && index >= dynamic.size) || (is_local() && index >= local.size)) {
        throw std::out_of_range("Index out of range");
    }
    return is_dynamic() ? dynamic.array[index] : local.array[index];
}

const short& ShortArray::operator[](size_t index) const {
    if ((is_dynamic() && index >= dynamic.size) || (is_local() && index >= local.size)) {
        throw std::out_of_range("Index out of range");
    }
    return is_dynamic() ? dynamic.array[index] : local.array[index];
}
