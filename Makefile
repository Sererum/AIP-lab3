COMPILER = g++
COMPILER_FLAGS = -Isrc -O2 -Wall -Wextra -std=c++17 -D_FORTIFY_SOURCE=2 -fstack-protector-strong -flto
OBJECTS = build/release/lab3.o build/release/my_string.o build/release/matrix.o 

build/release/output.out: $(OBJECTS)
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/output.out $(OBJECTS)

build/release/lab3.o: src/lab3.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/lab3.o -c src/lab3.cpp

build/release/my_string.o: src/my_string.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/my_string.o -c src/my_string.cpp

build/release/matrix.o: src/matrix.cpp
	$(COMPILER) $(COMPILER_FLAGS) -o build/release/matrix.o -c src/matrix.cpp

.PHONY: run
run: build/release/output.out
	build/release/output.out

.PHONY: clean
clean:
	rm -rf build/release/*
	rm -rf build/debug/*

DEBUG_FLAGS = -Isrc -Wall -Wextra -Werror -g -O0 -fsanitize=address -fsanitize=undefined -std=c++17
DEBUG_OBJECTS = build/debug/lab3.o build/debug/my_string.o build/debug/matrix.o

build/debug/debug.out: $(DEBUG_OBJECTS)
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/debug.out $(DEBUG_OBJECTS)

build/debug/lab3.o: src/lab3.cpp
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/lab3.o -c src/lab3.cpp

build/debug/my_string.o: src/my_string.cpp
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/my_string.o -c src/my_string.cpp

build/debug/matrix.o: src/matrix.cpp
	$(COMPILER) $(DEBUG_FLAGS) -o build/debug/matrix.o -c src/matrix.cpp

.PHONY: debug 
debug: build/debug/debug.out
	build/debug/debug.out

.PHONY: gdb 
gdb: build/debug/debug.out
	gdb build/debug/debug.out

