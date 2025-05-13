#include "worker_db.h"

WorkerData::WorkerData(const MyString& name, int age) 
    : name(name), age(age) {}

void WorkerDb::expand() {
	std::cout << capacity << std::endl;
    capacity *= 2;
    MyString* new_last_names = new MyString[10];
    WorkerData* new_data = new WorkerData[10];

    for (size_t i = 0; i < size; ++i) {
        new_last_names[i] = last_names[i];
        new_data[i] = data[i];
    }

    delete[] last_names;
    delete[] data;

    last_names = new_last_names;
    data = new_data;
}

WorkerDb::WorkerDb() 
    : size(0), capacity(4), 
	  last_names(new MyString[capacity]), 
	  data(new WorkerData[capacity]) {}	

WorkerDb::WorkerDb(size_t capacity) 
    : size(0), capacity(capacity), 
	  last_names(new MyString[capacity]), 
	  data(new WorkerData[capacity]) {}	

WorkerDb::~WorkerDb() {
    delete[] last_names;
    delete[] data;
}

const WorkerData& WorkerDb::operator[](const MyString& target) const {
    for (size_t i = 0; i < size; ++i) {
        if (last_names[i] == target) {
            return data[i];
        }
    }
    throw std::out_of_range("Key not found");
}

WorkerData& WorkerDb::operator[](const MyString& target) {
    for (size_t i = 0; i < size; ++i) {
        if (last_names[i] == target) {
            return data[i];
        }
    }

    if (size >= capacity) {
        expand();
    }

    last_names[size] = target;
    return data[size++];
}

bool WorkerDb::contains(const MyString& target) const {
    for (size_t i = 0; i < size; ++i) {
        if (last_names[i] == target) {
            return true;
        }
    }
    return false;
}

bool WorkerDb::remove(const MyString& target) {
    for (size_t i = 0; i < size; ++i) {
        if (last_names[i] == target) {
            for (size_t j = i; j < size - 1; ++j) {
                last_names[j] = last_names[j + 1];
                data[j] = data[j + 1];
            }
            --size;
            return true;
        }
    }
    return false;
}

// Iterator implementation
WorkerDb::Iterator::Iterator(WorkerDb* db, int index) 
    : db(db), index(index) {}

WorkerData& WorkerDb::Iterator::operator*() const {
    return db->data[index];
}

WorkerData* WorkerDb::Iterator::operator->() const {
    return &db->data[index];
}

WorkerDb::Iterator& WorkerDb::Iterator::operator++() {
    ++index;
    return *this;
}

WorkerDb::Iterator WorkerDb::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

bool WorkerDb::Iterator::operator==(const Iterator& other) const {
    return index == other.index && db == other.db;
}

bool WorkerDb::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

const MyString& WorkerDb::Iterator::key() const {
    return db->last_names[index];
}

WorkerDb::Iterator WorkerDb::begin() {
    return Iterator(this, 0);
}

WorkerDb::Iterator WorkerDb::end() {
    return Iterator(this, size);
}

void print_db(WorkerDb& db) {
	std::cout << "=== Workers Database ===\n";
	for (auto it = db.begin(); it != db.end(); ++it) {
		std::cout << it.key() << " -> Name: " << it->name << ", Age: " << it->age << "\n";
	}
	std::cout << "========================\n";
}

double get_avg_age(WorkerDb& db) {
	int count = 0;
	int total_age = 0;

	for (auto it = db.begin(); it != db.end(); ++it) {
		total_age += it->age;
		++count;
	}

	if (count == 0) {
		return 0.0; // Защита от деления на ноль
	}

	return static_cast<double>(total_age) / count;
}
