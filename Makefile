CC = g++
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
BUILD_DIR = build
OBJ_NAME = render
INCLUDE_PATHS = -I /opt/homebrew/include
LIBRARY_PATHS = -L /opt/homebrew/lib
COMPILER_FLAGS = -std=c++11 -O0 -g
LINKER_FLAGS = -lsdl2

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

clean:
	rm $(BUILD_DIR)/$(OBJ_NAME)
