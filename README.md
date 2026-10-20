# MiniVM — A Miniature Compiler and Virtual Machine

MiniVM is a small C++17 project that demonstrates the core stages of a compiler pipeline. It accepts a limited C-like language, tokenizes and parses the source, builds an Abstract Syntax Tree (AST), generates an Intermediate Representation (IR), and executes that IR in a register-based virtual machine.

> **Note:** MiniVM is an educational project implementing a small language subset. It is not a complete C/C++ compiler and does not generate NVIDIA PTX or GPU machine code.

## Features

- **Lexical Analysis:** Converts source code into tokens.
- **Recursive-Descent Parser:** Parses the supported program structure and arithmetic expressions.
- **Abstract Syntax Tree (AST):** Represents expressions and statements as a tree.
- **AST Printer:** Displays the parsed program structure.
- **Semantic Analysis:** Checks variable usage and duplicate declarations.
- **IR Generation:** Converts AST nodes into intermediate instructions.
- **IR Printer:** Displays the generated instructions.
- **Virtual Machine:** Executes the supported IR instructions.
- **Error Handling:** Detects errors such as malformed syntax, undefined variables, and division by zero.
- **Automated Testing:** Includes a custom C++ test suite and CTest integration.

## Compiler Architecture

```text
             Source Code
                  |
                  v
                 Lexer
                  |
                  v
                 Tokens
                  |
                  v
                 Parser
                  |
                  v
          Abstract Syntax Tree
                  |
                  v
          Semantic Analysis
                  |
                  v
          IR Generation
                  |
                  v
        Intermediate Representation
                  |
                  v
           Virtual Machine
                  |
                  v
           Execution Result
```

## Technology Stack

- **Language:** C++17
- **Build System:** CMake
- **Compiler:** GCC (MSYS2/MinGW on Windows)
- **Testing:** Custom C++ test executable and CTest

## Supported Language

MiniVM currently supports a limited C-like language.

Example:

```c
int main() {
    int result = 10 + 20 * 3;
    return result;
}
```

### Supported Constructs

- `int main()` function with a braced body
- Integer variable declarations with initializers
- `return` statements
- Integer literals
- Variable references
- Parenthesized expressions
- Addition (`+`)
- Subtraction (`-`)
- Multiplication (`*`)
- Division (`/`)
- Operator precedence
- Left-to-right associativity within each arithmetic precedence level

Features such as loops, conditional statements, assignment after declaration, multiple functions, and a full C/C++ type system are not currently implemented.

## Example Intermediate Representation

For the expression:

```c
int main() {
    int result = 10 + 20 * 3;
    return result;
}
```

MiniVM generates instructions similar to:

```text
LOAD_CONST R0, 10
LOAD_CONST R1, 20
LOAD_CONST R2, 3
MUL R3, R1, R2
ADD R4, R0, R3
STORE result, R4
LOAD R5, result
RETURN R5
```

The virtual machine executes these instructions and returns:

```text
Execution Result: 70
```

These are MiniVM's custom intermediate instructions, **not NVIDIA PTX instructions**.

## Project Structure

The following tree illustrates the intended project organization:

```text
MiniVM/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── ast.hpp
│   ├── ast_printer.hpp
│   ├── ir.hpp
│   ├── ir_printer.hpp
│   ├── lexer.hpp
│   ├── parser.hpp
│   ├── semantic_analyzer.hpp
│   └── vm.hpp
├── src/
│   ├── ast_printer.cpp
│   ├── ir.cpp
│   ├── ir_printer.cpp
│   ├── lexer.cpp
│   ├── main.cpp
│   ├── parser.cpp
│   ├── semantic_analyzer.cpp
│   └── vm.cpp
├── tests/
│   └── minivm_tests.cpp
└── examples/
```

*Note: This tree describes the expected organization. Keep only files and folders that actually exist in your repository.*

## Getting Started

### Requirements

- C++17-compatible compiler
- CMake 3.20 or newer
- MinGW Makefiles generator or another supported CMake generator

### Build on Windows

Open Command Prompt or the VS Code terminal in the project directory.

Configure the project:

```cmd
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe
```

Build:

```cmd
cmake --build build
```

If your existing `build` directory is already configured correctly, you can usually run only:

```cmd
cmake --build build
```

### Run MiniVM

```cmd
build\minivm.exe
```

The current implementation uses a sample source program embedded in `main.cpp`.

## Running Tests

Run the automated test executable:

```cmd
build\minivm_tests.exe
```

Alternatively, use CTest:

```cmd
ctest --test-dir build --output-on-failure
```

### Test Results

During development, the following results were obtained:

- **12 test cases passed**
- **0 test cases failed**
- CTest completed successfully

The tests cover arithmetic operations, operator precedence, parentheses, and selected error-handling cases.

Run the tests again after code changes to verify the current state.

## Current Limitations

- The language is an educational subset, not a complete implementation of C or C++.
- The intermediate representation is custom and is not NVIDIA PTX.
- General integer-overflow protection is not implemented.
- Semantic analysis uses a simple function-level variable set; nested scopes and comprehensive type checking are not implemented.
- Error diagnostics and invalid-token handling can be improved.
- Source-file input is not yet implemented; the example program is currently embedded in `main.cpp`.
- Test coverage is not exhaustive.

## Project Status

The core compiler and virtual-machine pipeline has been implemented, and the initial automated test suite has passed.

Potential future improvements include expanded edge-case testing, stronger diagnostics, source-file input, and additional language features.

## License

No license has been specified yet.
