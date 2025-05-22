# TODO List in C

A simple console-based TODO list written in C.

## FEATURES:

- Add tasks with title and completion status
- Toggle task status (done/not done)
- Delete tasks by ID
- Save task list to todos.txt
- Load tasks from file on startup
- Interactive menu interface

---

## PROJECT STRUCTURE:

```sh
 lesson-c-todo
 ├── include
 │   ├── todo.h               # Header file defining the Todo data structure and related declarations
 │   └── ui.h                 # Header file declaring UI-related functions (menus, input, output)
 ├── src
 │   ├── file.c               # Source file handling file operations (loading, saving todos)
 │   ├── main.c               # Main program entry point and application logic
 │   ├── todo.c               # Source file implementing todo management (add, edit, delete todos)
 │   └── ui.c                 # Source file implementing user interface functions
 ├── CMakeLists.txt           # CMake build configuration file
 ├── README.md                # Project documentation and overview
 └── toolchain-mingw.cmake    # CMake toolchain file for cross-compiling to Windows using MinGW-w64
```

---

## BUILDING:

#### Using CMake:

```sh
# Release
cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release
make --directory build

# Debug
cmake -B build-debug -S . \
    -DCMAKE_BUILD_TYPE=Debug
make --directory build-debug

# Run with debugging
gdb build-debug/todos

# Analyze memory leak
valgrind --leak-check=full --show-leak-kinds=all build-debug/todos
```

#### Using CMake for Windows

```sh
# Release
cmake -B build-release-windows -S . \
    -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake \
    -DCMAKE_BUILD_TYPE=Release
cmake --build build-release-windows

# Debug
cmake -B build-debug-windows -S . \
    -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake \
    -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug-windows
```

#### Direct compilation with clang:

```sh
# Release
clang -O3 -DNDEBUG -Iinclude src/*.c -o todos_release

# Debug
clang -g -O0 -Iinclude src/*.c -o todos_debug

# Run with debugging
gdb todos_debug

# Analyze memory leak
clang -g -O1 -fsanitize=address -fno-omit-frame-pointer -Iinclude src/*.c -o todos_asan
./todos_asan
```

#### Using dockcross

```sh
docker run --rm dockcross/linux-x64 > ./dockcross
chmod +x ./dockcross

./dockcross cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Windows
./dockcross cmake --build build --config Release
```

## USAGE:

1. Run the program:

```sh
./todos
```

2. Menu options:

- Add task
- Toggle task status
- Delete task
- Save to file
- Load from file
- Exit

## TECHNICAL DETAILS:

- Tasks stored in id;title;done format
- Unique task IDs (non-repeating after deletion)
- C23 compatible code

## REQUIREMENTS:

- C compiler (clang/gcc)
- CMake (optional)
