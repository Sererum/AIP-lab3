#pragma once

#include "libs.h"

class IFile {
public:
	virtual bool is_open() const = 0;

    virtual bool can_read() const = 0;
    virtual bool can_write() const = 0;
    virtual size_t write(const void* buf, size_t n_bytes) = 0;
	virtual size_t read(void* buf, size_t max_bytes) = 0; 

    virtual long tell() const = 0;
    virtual bool seek(long offset) = 0;
	virtual bool close() = 0;

	virtual ~IFile() = default;
};

