#pragma once

#include "libs.h"
#include "my_string.h"

struct WorkerData {
    MyString name;
    int age;

    WorkerData(const MyString& name = "", int age = 0);
};

class WorkerDb {
private:
    size_t size;
    size_t capacity;
    MyString* last_names;
    WorkerData* data;
    
    void expand();

public:
 	WorkerDb();
    WorkerDb(size_t capacity);
    ~WorkerDb();

    const WorkerData& operator[](const MyString& target) const;
    WorkerData& operator[](const MyString& target);
    
    bool contains(const MyString& target) const;
    bool remove(const MyString& target);

    class Iterator {
    private:
        WorkerDb* db;
        int index;
        
    public:
        Iterator(WorkerDb* db, int index);
        WorkerData& operator*() const;
        WorkerData* operator->() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        const MyString& key() const;
    };

    Iterator begin();
    Iterator end();
};

void print_db(WorkerDb& db);
double get_avg_age(WorkerDb& db);

