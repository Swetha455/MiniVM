#ifndef MINIVM_IR_PRINTER_HPP
#define MINIVM_IR_PRINTER_HPP

#include "ir.hpp"

#include <string>
#include <vector>

class IRPrinter {
public:
    std::string print(
        const std::vector<Instruction>& instructions
    );

private:
    std::string opcodeToString(OpCode opcode);
};

#endif