#pragma once

#include "libs.h"

/*[false, true, false, false]
0, 1, 2, 3

Reference()

 00010000 
[01001011]

[01001011] | 0001000 = [01011011]
[01001011] & 1011111 = [00001011]

00010000 & 01001011 = 0
*/

class BoolArray {
private:
    unsigned char* data;
    size_t bit_count;

    class Reference {
    private:
        unsigned char& byte;
        unsigned char mask;

    public:
        Reference(unsigned char& byte, unsigned char mask);

        operator bool() const;             // Чтение бита
        Reference& operator=(bool value); // Запись бита
        Reference& operator=(const Reference& other); // Присваивание из другого Reference
        bool operator~() const;
		bool get_value() const { return bool(); }
        Reference& operator=(int) = delete; // Защита от случайных приведений
    };

public:
    explicit BoolArray(size_t size = 0, bool value = false);
    BoolArray(const BoolArray& other);
    BoolArray(BoolArray&& other);
    ~BoolArray();

    BoolArray& operator=(const BoolArray& other);
    BoolArray& operator=(BoolArray&& other);

    Reference operator[](size_t index);
    bool operator[](size_t index) const;

    void resize(size_t new_size, bool value = false);

    size_t size() const { return bit_count; }

    friend std::ostream& operator<<(std::ostream& os, const BoolArray& arr);
};
