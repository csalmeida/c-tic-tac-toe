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
EMBED_IMAGES := ./embed_images.sh
# SOURCES := $(shell find $(SRC) -name "*.c") # Finds files to compile.

.PHONY: clean all

# Build for all targets:
.PHONY: all
all: clean assets mac-arm64 win64

# Cleans the bin directory and runs the executable.
run: clean all
	./$(BIN)/$(EXECUTABLE)

# Formats source code:
# FIXME: Not in use because it formats game grid array to a more unreadable format.
# Needs a rules file.
.PHONY: format
format:
	clang-format -i src/**/*.c src/**/*.h

# Converts assets into byte array header files.
# To be included in the final program.
.PHONY: assets
assets: 
	$(EMBED_IMAGES)

$(BIN)/$(EXECUTABLE): $(SRC)/$(FILE_NAME).c
	$(CC) $(C_FLAGS) $^ -o $@ -I$(INCLUDE_PATHS) -L$(LIBRARY_PATHS) $(LIBRARIES)

mac-arm64: $(SRC)/$(FILE_NAME).c 
	$(CC) $(C_FLAGS) $^ -target arm64-apple-macos11 -o $(BIN)/mac-arm64/$(EXECUTABLE)_mac_arm64 -I$(INCLUDE_PATHS) -L$(LIBRARY_PATHS) $(LIBRARIES)

win64: $(SRC)/$(FILE_NAME).c
	x86_64-w64-mingw32-gcc $(C_FLAGS) $^ -o $(BIN)/win64/$(EXECUTABLE)_win64.exe -Iwindows_include -Lwindows_lib -lmingw32 -lSDL2 -lSDL2main -lSDL2_image -mwindows `sdl2-config --libs`

# WASM compatible compiler and flags:
EMCC 		:= emcc
EMCC_FLAGS := -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=0 -O0 --std=c99 -Wall
# @FIXME: This command compiles the program but it doesn't work due to an issue with how SDL and emscripten main loop works:
wasm: $(SRC)/$(FILE_NAME).c
	$(EMCC) $^ $(EMCC_FLAGS) -I$(INCLUDE_PATHS) -L$(LIBRARY_PATHS) -o $(BIN)/wasm/$(EXECUTABLE).html

# Removes main and main.* folders, keeps sdl2-config.
# It also removes embedded asset files.
clean:
	- rm -f ./bin/mac-arm64/$(EXECUTABLE)
	- rm -f ./bin/mac-arm64/$(EXECUTABLE)_
	- rm -rf ./bin/mac-arm64/$(EXECUTABLE).*
	- rm -f ./bin/win64/$(EXECUTABLE)
	- rm -f ./bin/win64/$(EXECUTABLE)_
	- rm -rf ./bin/win64/$(EXECUTABLE).*
	- rm -rf ./src/assets/*.h

# The final command should look like:
# gcc `sdl2-config --cflags` -ggdb3 -O0 --std=c99 -Wall src/main.c -o bin/main -Iinclude -Llib -lSDL2 -lSDL2_image
