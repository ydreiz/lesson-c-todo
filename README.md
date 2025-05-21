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
todo_project/
├── include/
│   └── todo.h          # Structure definitions and function prototypes
│   └── ui.h            # Structure definitions and function prototypes
├── src/
│   ├── main.c          # Entry point, menu logic
│   ├── todo.c          # Task management
│   ├── file.c          # File operations
│   └── ui.c            # User interface
├── Makefile            # Build configuration
└── todos.txt           # Task storage (created on startup)
```
---

## BUILDING:

#### Using CMake:
```sh
mkdir build && cd build
cmake ..
make
```

#### Using CMake for Windows
```sh
mkdir build-win && cd build-win
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake
cmake --build .
```

#### Direct compilation with clang:
```sh
clang -Iinclude src/*.c -o todos
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
