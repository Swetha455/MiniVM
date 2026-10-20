MiniVM — A Miniature Compiler and Virtual Machine

MiniVM is a small C++17 project that demonstrates the core stages of a compiler pipeline. It accepts a limited C-like language, tokenizes and parses the source, builds an Abstract Syntax Tree (AST), generates an intermediate representation (IR), and executes that IR in a register-based virtual machine.

Scope: MiniVM is an educational compiler/interpreter for a small language subset. It is not a complete C/C++ compiler and does not generate NVIDIA PTX or GPU machine code.

Features

Lexical analysis: Converts source text into tokens.

Recursive-descent parsing: Parses the supported program structure and arithmetic expressions.

Abstract Syntax Tree: Represents number literals, variable references, binary expressions, variable declarations, and return statements.

AST printer: Displays the parsed program structure.

Semantic analysis: Checks variable use and duplicate declarations within the currently supported function-level scope.

Intermediate Representation: Converts AST nodes into simple register-based instructions.

IR printer: Displays generated instructions.

Virtual machine: Executes the supported IR instructions.

Error handling: Includes checks for issues such as malformed syntax, undefined variables, and division by zero.

Automated tests: Uses a standalone test executable and CTest.

Compiler Pipeline

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
    AST
    |
    v
Semantic Analysis
    |
    v
 IR Generation
    |
    v
 IR Instructions
    |
    v
 Virtual Machine
    |
    v
Execution Result

Technology

Language: C++17

Build system: CMake

Compiler used during development: GCC via MSYS2/MinGW on Windows

Testing: Custom C++ test executable and CTest

Supported Language Subset

MiniVM currently supports a limited form of a C-like program:

int main() {
    int result = 10 + 20 * 3;
    return result;
}

Implemented constructs include:

A single int main() function with a braced body

Integer variable declarations with initializers, such as int x = 10;

return statements

Integer literals

Variable references

Parenthesized expressions

Arithmetic operators: +, -, *, /

Operator precedence and left-to-right associativity within each precedence level

This is a deliberately small language. Features such as assignment after declaration, conditional statements, loops, functions with parameters, multiple functions, and a full C/C++ type system are not currently implemented.

Example Intermediate Representation

For this input:

int main() {
    int result = 10 + 20 * 3;
    return result;
}

MiniVM generates instructions similar to:

LOAD_CONST R0, 10
LOAD_CONST R1, 20
LOAD_CONST R2, 3
MUL R3, R1, R2
ADD R4, R0, R3
STORE result, R4
LOAD R5, result
RETURN R5

The virtual machine executes these instructions and returns 70.

These are MiniVM's own IR instructions; they are not NVIDIA PTX instructions.

Project Structure

MiniVM/
├── CMakeLists.txt
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
├── examples/
└── build/                 # Generated build files; usually not committed

The exact contents of examples/ depend on the files added to the repository.

Requirements

A C++17-compatible compiler

CMake 3.20 or newer

Make or another build tool supported by your CMake generator

The commands below use Windows Command Prompt and the MinGW Makefiles generator.

Build on Windows (MSYS2/MinGW)

From the project root:

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe
cmake --build build

If the build directory was already configured with the MinGW Makefiles generator, rebuilding usually only requires:

cmake --build build

If CMake reports that the build directory was configured with a different generator, remove the generated build directory and rerun the configure command above. Only delete the generated build directory, not your source files.

Run MiniVM

After a successful build:

build\minivm.exe

The current main.cpp contains a sample program, so running the executable processes that built-in example.

Run the Automated Tests

Run the test executable:

build\minivm_tests.exe

Or run the registered test through CTest:

ctest --test-dir build --output-on-failure

During development, the test suite passed 12 test cases: seven arithmetic/expression cases and five error-handling cases. The CTest command also passed. Re-run the tests after any code changes to confirm the current state.

Current Limitations

The language is intentionally limited and is not C or C++ compliant.

The IR is a custom educational representation and is not PTX.

The virtual machine uses C++ int arithmetic; general integer-overflow protection has not been implemented.

Semantic analysis uses a simple function-level variable set; nested lexical scopes and richer type checking are not implemented.

Error diagnostics and invalid-token handling can be improved.

The program entry point currently uses a source example embedded in main.cpp; loading source code from a file is not yet implemented.

Test coverage is useful but not exhaustive.

Project Status

The core educational pipeline is implemented and basic automated tests are passing. Further improvements may include broader edge-case tests, stronger diagnostics, source-file input, and additional language features.
