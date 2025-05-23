# Console TODO List in C

> A strict, minimalistic implementation of a personal task manager in C with a simple menu and persistent storage between sessions.

## DESCRIPTION

This is an educational project — a console TODO list written in C (C23), supporting basic todo management operations: adding, toggling status, deleting, saving, and loading from a file.

**Why C?**
- Minimal dependencies, maximum memory control.
- Educational value: the project demonstrates struct usage, file operations, and user input handling at a low level.

---

## FEATURES

- [x] Add todo with a title, completion status, and unique ID
- [x] Toggle todo status (done/not done)
- [x] Delete todos by ID
- [x] Save todo list to `todos.txt` and load on startup
- [x] Simple text menu interface
- [ ] No support for subtodo, categories, or deadlines — intentionally omitted for focus on the basics

---

## PROJECT STRUCTURE

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

## BUILDING

**Recommended:** CMake >= 3.20, GCC or Clang (C23 support).

### Linux/macOS

```sh
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/todos
```
For debugging:
```sh
cmake -B build-debug -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
gdb build-debug/todos
```

### Windows (cross-compilation via MinGW)

```sh
cmake -B build-win -S . -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake
cmake --build build-win
```

### Quick build without CMake

```sh
clang -O2 -Iinclude src/*.c -o todos
# or
gcc -O2 -Iinclude src/*.c -o todos
```

---

## USAGE

1. Run the program
2. Follow the menu:
    - Add todo
    - Toggle todo status
    - Edit title
    - Delete todo
    - Save todos
    - Load todos
    - Exit

Todos are saved in the `id;title;done` format in a text file.

---

## TECHNICAL DETAILS

- Todos stored in `id;title;done` format
- Unique todo IDs (non-repeating after deletion)
- C23 compatible code

---

## REQUIREMENTS

- C compiler (clang/gcc)
- CMake (optional)
- Valgrind/AddressSanitizer for memory analysis (optional)

---

## DEBUGGING

### 1. Step-by-Step Debugging with GDB

Start the program with GDB:

```sh
gdb build-debug/todos
# or
gdb todos_debug
```

Typical GDB workflow:
- `break main` — Set a breakpoint at main().
- `run` — Start the program.
- `next` / `step` — Step through code line by line.
- `print variable` — Inspect variable values.
- `backtrace` — View the call stack on crash.

**Counterpoint:** If you’re not using GDB, you risk missing subtle bugs, especially in pointer logic and memory handling.

### 3. Memory Leak and Undefined Behavior Detection

- Memory leak check:
    ```sh
    valgrind --leak-check=full --show-leak-kinds=all build-debug/todos
    ```
- Run with AddressSanitizer:
    ```sh
    clang -g -O1 -fsanitize=address -fno-omit-frame-pointer -Iinclude src/*.c -o todos_asan
    ./todos_asan
    ```

---

## LIMITATIONS & CRITICAL VIEW

- **No search, sort, categories, or deadlines:** Only basic todo management is supported. This limits practical applicability for complex workflows.
- **No unit tests or CI/CD:** Memory leaks and regressions are possible. Consider integrating tests and automation for better maintainability.
- **No localization or extended UI:** Only a basic English text menu is supported.
- **No concurrency or multi-user support:** Only single-user, single-process operation.

**Counterpoint:**
While these limitations keep the codebase simple and educational, they restrict real-world scalability and collaboration. For practical adoption, future work should address these areas.

---

## FUTURE IMPROVEMENTS

- Add modular/unit tests (e.g., with CMocka)
- Implement export/import in CSV, JSON, or other formats
- Support for todo search, sort, and filter
- Add todo categories, deadlines, and priorities
- Multi-user and/or client-server support
- Internationalization/localization
- Refactor menu to be dynamically generated from code to avoid documentation drift

---

## LICENSE

MIT (or clarify as needed).

---

> **Critical Note:**
> The project is intentionally minimalist and educational, but its current state limits practical use and long-term maintainability. Prioritizing testing, extensibility, and user experience will be essential for future development.
