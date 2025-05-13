#pragma once

#include "ifile.h"
#include "libs.h"

class BaseFile : public IFile {
public:
    BaseFile();	 
    BaseFile(const char* path, const char* mode); 
    explicit BaseFile(FILE* f);  
    ~BaseFile();

    BaseFile(const BaseFile&) = delete;
    BaseFile& operator=(const BaseFile&) = delete;
    BaseFile(BaseFile&& other);
    BaseFile& operator=(BaseFile&& other);

    bool is_open() const override;
    bool can_read() const override;
    bool can_write() const override;
    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);
    long tell() const;
    bool seek(long offset);
	bool close();

    size_t write(const void* buf, size_t n_bytes) override { return write_raw(buf, n_bytes); }
    size_t read(void* buf, size_t max_bytes) override { return read_raw(buf, max_bytes); }

private:
    FILE* file;       
    bool owns_file;   
    const char* mode; 
};

// класс для работы с текстовыми файлами
class TextFile : public BaseFile {
public:
    TextFile(const char* path, const char* mode) : BaseFile(path, mode) {}
    ~TextFile() = default;

    void write_line(const char* line);
    size_t read_line(char* buffer, size_t buffer_size); 
};

// класс для только-чтения файлов
class ReadOnlyFile : public BaseFile {
public:
    ReadOnlyFile(const char* path) : BaseFile(path, "r") {}
    ~ReadOnlyFile() = default;

    size_t write_raw(const void*, size_t) {
        std::cerr << "Write operation not allowed in ReadOnlyFile\n";
        return 0;
    }

    size_t write(const void*, size_t) { return 0; }
};
