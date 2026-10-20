#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include "lexer.hpp"
#include "parser.hpp"
#include "ast_printer.hpp"
#include "ir.hpp"
#include "ir_printer.hpp"
#include "vm.hpp"

int main() {
    const std::string source = R"(
        int main() {
            int result = 20 - 8;
            return result;
    }
)";

    try {
        // Stage 1: Lexical analysis
        Lexer lexer(source);
        std::vector<Token> tokens = lexer.tokenize();

        std::cout << "MiniVM Lexer: SUCCESS\n";
        std::cout << "Tokens generated: "
                  << tokens.size() << "\n\n";

        // Stage 2: Parsing
        Parser parser(tokens);
        Program program = parser.parse();

        std::cout << "MiniVM Parser: SUCCESS\n";
        std::cout << "Statements parsed: "
                  << program.statements.size() << "\n\n";

        // Stage 3: AST printing
        ASTPrinter astPrinter;

        std::cout << astPrinter.print(program) << '\n';

        // Stage 4: IR generation
        IRGenerator generator;

        std::vector<Instruction> instructions =
            generator.generate(program);

        std::cout << "IR Generation: SUCCESS\n\n";

        // Stage 5: IR printing
        IRPrinter irPrinter;

        std::cout << irPrinter.print(instructions);
        std::cout << "\nExecuting program...\n";
        VirtualMachine vm;
        int result = vm.execute(instructions);
        std::cout << "Execution Result: " << result << '\n';

    } catch (const std::exception& error) {
        std::cerr << "Compilation error: "
                  << error.what() << '\n';

        return 1;
    }

    return 0;
}