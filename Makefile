# Set the compiler:
CC       := gcc

# Set compiler flags:
C_FLAGS := `sdl2-config --cflags` -ggdb3 -O0 --std=c99 -Wall

# The file name to be compiled.
# Changes executable name:
FILE_NAME := main

# bin is where executables are saved to.
# src is where source code is located.
BIN     := bin
SRC     := src

# Paths to include in building the program:
INCLUDE_PATHS := include
LIBRARY_PATHS = lib

# Specify the libraries being used:
LIBRARIES   := -lSDL2 -lSDL2_image # Don't forget that -l is the option
LINKED_LIRARIES := include
EXECUTABLE  := $(FILE_NAME)
# SOURCES := $(shell find $(SRC) -name "*.c") # Finds files to compile.

.PHONY: clean all

# Attempt to execute the program:
all: $(BIN)/$(EXECUTABLE)

# Cleans the bin directory and runs the executable.
run: clean all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/$(FILE_NAME).c
	$(CC) $(C_FLAGS) $^ -o $@ -I$(INCLUDE_PATHS) -L$(LIBRARY_PATHS) $(LIBRARIES)

mac-arm64: $(SRC)/$(FILE_NAME).c
	$(CC) $(C_FLAGS) $^ -target arm64-apple-macos11 -o $(BIN)/mac-arm64/$(EXECUTABLE)_mac_arm64 -I$(INCLUDE_PATHS) -L$(LIBRARY_PATHS) $(LIBRARIES)

win64: $(SRC)/$(FILE_NAME).c
	x86_64-w64-mingw32-gcc $(C_FLAGS) $^ -o $(BIN)/win64/$(EXECUTABLE)_win64.exe -Iwindows_include -Lwindows_lib -lmingw32 -lSDL2 -lSDL2main -lSDL2_image -mwindows `sdl2-config --libs`

# Removes main and main.* folders, keeps sdl2-config:
clean:
	- rm -f ./bin/mac-arm64/$(EXECUTABLE)
	- rm -f ./bin/mac-arm64/$(EXECUTABLE)_
	- rm -rf ./bin/mac-arm64/$(EXECUTABLE).*
	- rm -f ./bin/win64/$(EXECUTABLE)
	- rm -f ./bin/win64/$(EXECUTABLE)_
	- rm -rf ./bin/win64/$(EXECUTABLE).*

# The final command should look like:
# gcc `sdl2-config --cflags` -ggdb3 -O0 --std=c99 -Wall src/main.c -o bin/main -Iinclude -Llib -lSDL2 -lSDL2_image
