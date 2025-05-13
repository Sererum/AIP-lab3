#include "base_file.h"

BaseFile::BaseFile() 
    : file(nullptr), owns_file(false), mode(nullptr) {}

BaseFile::BaseFile(const char* path, const char* mode_str) 
    : owns_file(true), mode(mode_str) {
    file = std::fopen(path, mode_str);
    if (!file) {
        std::fprintf(stderr, "Failed to open file: %s\n", path);
    }
}

BaseFile::BaseFile(FILE* f) 
    : file(f), owns_file(false), mode(nullptr) {}

BaseFile::~BaseFile() {
    if (owns_file && file) {
        std::fclose(file);
    }
}

bool BaseFile::is_open() const {
    return file != nullptr;
}

bool BaseFile::can_read() const {
    if (!is_open()) return false;
    return std::strchr(mode, 'r') != nullptr;
}

bool BaseFile::can_write() const {
    if (!is_open()) return false;
    return std::strchr(mode, 'w') != nullptr ||
           std::strchr(mode, 'a') != nullptr ||
           std::strchr(mode, '+') != nullptr;
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!is_open() || !can_write()) return 0;
    return std::fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
	if (!is_open() || !can_read()) {
        std::cerr << "Ошибка: файл не открыт или недоступен для чтения." << std::endl;
        return 0;
    }

    size_t bytes_read = std::fread(buf, 1, max_bytes, file);
	static_cast<char*>(buf)[bytes_read] = '\0';
    
    if (bytes_read == 0 && std::ferror(file)) {
        std::cerr << "Ошибка: сбой при чтении файла!" << std::endl;
    }

	return bytes_read;
}

long BaseFile::tell() const {
    if (!is_open()) return -1;
    return std::ftell(file);
}

bool BaseFile::seek(long offset) {
    if (!is_open()) return false;
    return std::fseek(file, offset, SEEK_SET) == 0;
}

bool BaseFile::close() {
    if (owns_file && file) {
        std::fclose(file);
		owns_file = false;
		file = nullptr;
		return true;
    }
	return false;
}

void TextFile::write_line(const char* line) {
    // записываем строку + символ '\0' + '\n'
    size_t len = std::strlen(line);
    write(line, len + 1); 
    write("\n", 1);     
}

size_t TextFile::read_line(char* buffer, size_t buffer_size) {
    size_t bytesRead = 0;
    char c;
    while (bytesRead < buffer_size - 1) {
        size_t size_read = read(&c, 1);
        if (size_read == 0) break; 
        buffer[bytesRead++] = c;
        if (c == '\n') break; 
    }
    buffer[bytesRead] = '\0';
    return bytesRead;
}

BaseFile::BaseFile(BaseFile&& other)
    : file(other.file), owns_file(other.owns_file), mode(other.mode)
{
    other.file = nullptr;
    other.owns_file = false;
}

BaseFile& BaseFile::operator=(BaseFile&& other) {
    if (this != &other) {
        if (owns_file && file) {
            std::fclose(file);
        }

        file = other.file;
        owns_file = other.owns_file;
        mode = other.mode;

        other.file = nullptr;
        other.owns_file = false;
    }
    return *this;
}
