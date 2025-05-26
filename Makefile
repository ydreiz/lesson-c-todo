CC = clang
CFLAGS = -Wall -Wextra -std=c23 -Iinclude -g

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build-test

APP_NAME = todos
TEST_NAME = tests_runner

APP_SRC = $(filter-out $(SRC_DIR)/todos.c, $(wildcard $(SRC_DIR)/*.c))
APP_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(APP_SRC))

TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRC))

.PHONY: all clean test

all: $(BUILD_DIR) $(APP_OBJ) $(BUILD_DIR)/$(TEST_NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_NAME): $(APP_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(BUILD_DIR)/$(TEST_NAME)
	./$(BUILD_DIR)/$(TEST_NAME)

clean:
	rm -rf $(BUILD_DIR)

build/release:
	cmake -B build -S . -D CMAKE_BUILD_TYPE=Release
	cmake --build build

build/debug:
	cmake -B build-debug -S . -D CMAKE_BUILD_TYPE=Debug
	cmake --build build-debug

build/win:
	cmake -B build-win -S . -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake
	cmake --build build-win

run/relese: build/release
	./build/$(APP_NAME)

run/debug: build/debug
	gdb build-debug/$(APP_NAME)

run/test/debug: all test
	gdb build-test/$(TEST_NAME)

