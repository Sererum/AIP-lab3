#include "bool_array.h"

BoolArray::Reference::Reference(unsigned char& byte, unsigned char mask)
    : byte(byte), mask(mask) {}

BoolArray::Reference::operator bool() const {
    return (bool)(byte & mask);
}

BoolArray::Reference& BoolArray::Reference::operator=(bool value) {
    if (value)
        byte |= mask;
    else
        byte &= ~mask;
    return *this;
}

BoolArray::Reference& BoolArray::Reference::operator=(const Reference& other) {
    return *this = other.get_value();
}

bool BoolArray::Reference::operator~() const {
    return !bool();
}

BoolArray::BoolArray(size_t size, bool value)
    : bit_count(size) {
    size_t byte_count = std::ceil(bit_count / 8.);
    data = new unsigned char[byte_count];
    std::memset(data, value ? 0xFF : 0x00, byte_count);
}

BoolArray::BoolArray(const BoolArray& other)
    : bit_count(other.bit_count) {
    size_t byte_count = std::ceil(bit_count / 8.);
    data = new unsigned char[byte_count];
    std::memcpy(data, other.data, byte_count);
}

BoolArray::BoolArray(BoolArray&& other)
    : data(other.data), bit_count(other.bit_count) {
    other.data = nullptr;
    other.bit_count = 0;
}

BoolArray::~BoolArray() {
    delete[] data;
}

BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data;
        bit_count = other.bit_count;
        size_t byte_count = std::ceil(bit_count / 8.);
        data = new unsigned char[byte_count];
        std::memcpy(data, other.data, byte_count);
    }
    return *this;
}

BoolArray& BoolArray::operator=(BoolArray&& other) {
    if (this != &other) {
        delete[] data;
        data = other.data;
        bit_count = other.bit_count;
        other.data = nullptr;
        other.bit_count = 0;
    }
    return *this;
}

BoolArray::Reference BoolArray::operator[](size_t index) {
	if (index >= bit_count)
	   throw std::runtime_error("...");

    return Reference(data[index / 8], 1 << (index % 8));
}

bool BoolArray::operator[](size_t index) const {
	if (index >= bit_count)
	   throw std::runtime_error("..."); 

    return (data[index / 8] >> (index % 8)) & 1;
}

void BoolArray::resize(size_t new_size, bool value) {
    if (new_size == bit_count) return;

    size_t old_byte_count = std::ceil(bit_count / 8.);
    size_t new_byte_count = std::ceil(new_size / 8.);

    unsigned char* new_data = new unsigned char[new_byte_count];

    if (data) {
        if (new_size > bit_count) {
            // Расширяем: копируем старые данные
            std::memcpy(new_data, data, old_byte_count);
            // Заполняем новые биты
            std::memset(new_data + old_byte_count, value ? 0xFF : 0x00, new_byte_count - old_byte_count);
        } else {
            // Сужаем: копируем только нужное
            std::memcpy(new_data, data, new_byte_count);
            // Если новый размер не делится на 8, обрезаем лишние биты в последнем байте
            /*size_t last_bit_index = new_size % 8;
            if (last_bit_index != 0) {
                new_data[new_size / 8] &= (1 << last_bit_index) - 1;
            }*/

			//[000000|10] & (00000100 - 1) -> 00000011

        }
    } else {
        std::memset(new_data, value ? 0xFF : 0x00, new_byte_count);
    }

    delete[] data;
    data = new_data;
    bit_count = new_size;
}

std::ostream& operator<<(std::ostream& os, const BoolArray& arr) {
    os << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i > 0) os << ", ";
        os << (bool(arr[i]) ? "true" : "false");
    }
    os << "]";
    return os;
}
