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
- [x] Edit title of existing todo
- [x] Toggle todo status (done/not done)
- [x] Delete todos by ID
- [x] Save todo list to `todos.txt` and load on startup
- [x] Simple text menu interface
- [x] Minimalistic, framework-free test runner for core logic (see TESTING below)
- [ ] No support for subtodo, categories, or deadlines — intentionally omitted for focus on the basics

---

## PROJECT STRUCTURE

```sh
todos-c
├── include
│   ├── errors.h             # Header file declaring error codes and error handling utilities
│   ├── print.h              # Header file declaring functions and utilities for formatted output and printing to the console
│   ├── test.h               # Header file declaring test-related functions
│   ├── todo.h               # Header file defining the Todo data structure and related declarations
│   ├── tui.h                # Header file declaring UI-related functions (menus, input, output)
├── src
│   ├── errors.c             # Source file implementing error handling logic
│   ├── file.c               # Source file handling file operations (loading, saving todos)
│   ├── print.c              # Source file implementing formatted output and printing utilities for the console
│   ├── tets.c               # Test program entry point and application logic
│   ├── todo.c               # Source file implementing todo management (add, edit, delete todos)
│   ├── todos.c              # Todos program entry point and application logic
│   └── tui.c                # Source file implementing user interface functions
├── tests
│   ├── test_todo.c          # Manual tests, entry point is main()
│   └── ...                  # Additional test files
├── Makefile                 # Build and test automation
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
# Or
make build/run
```

For debugging:

```sh
cmake -B build-debug -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
gdb build-debug/todos
# Or
make build/run
```

### Windows (cross-compilation via MinGW)

```sh
cmake -B build-win -S . -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw.cmake
cmake --build build-win
# Or
make build/win
```

### Quick build without CMake

```sh
clang -O2 -Iinclude src/*.c -o todos
# or
gcc -O2 -Iinclude src/*.c -o todos
```

### Build and run tests

```sh
make
make test
```

> The test runner is framework-free and simply returns a nonzero exit code on failure.
> You can inspect or expand tests in the `tests/` directory.

### Clean build artifacts test

```sh
make clean
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
- make
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

## TESTING

- Tests are implemented manually, without any external frameworks.
- The test entry point is `tests/test_todo.c` (and others), with a main() function invoking various test routines.
- Test runner returns a nonzero exit code if any test fails.
- Run tests via `make test`.
- Tests cover basic logic: creation, toggling, deletion, file I/O, and some edge cases.

**Critical perspective:**
This approach is simple and transparent, but not scalable. There is no automatic test discovery, failure reporting, or CI integration. As the project grows, maintaining custom runners becomes error-prone and inefficient.
For robust projects, a lightweight C test framework (e.g., CMocka, Check, Unity) is strongly recommended, along with automated CI/CD and coverage reporting.

**Alternative:**
If future maintainability or collaboration is a goal, consider migrating to a real test framework. This would make tests easier to write, run, and automate — and would unlock integration with modern tooling.

---

## LIMITATIONS & CRITICAL VIEW

- **No search, sort, categories, or deadlines:** Only basic todo management is supported. This limits practical applicability for complex workflows.
- **Manual, minimal test suite:** Testing is limited and not automated; coverage is likely incomplete, and CI/CD is absent.
- **No localization or extended UI:** Only a basic English text menu is supported.
- **No concurrency or multi-user support:** Only single-user, single-process operation.

**Counterpoint:**
These constraints keep the codebase simple and educational, but also make it difficult to scale, maintain, or adapt to real-world use cases. For anything beyond a learning project, addressing these issues will become essential.

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
