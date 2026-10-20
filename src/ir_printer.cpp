#include "ir_printer.hpp"

#include <sstream>
#include <stdexcept>

std::string IRPrinter::opcodeToString(OpCode opcode) {
    switch (opcode) {
        case OpCode::LOAD_CONST: return "LOAD_CONST";
        case OpCode::LOAD:       return "LOAD";
        case OpCode::STORE:      return "STORE";
        case OpCode::ADD:        return "ADD";
        case OpCode::SUB:        return "SUB";
        case OpCode::MUL:        return "MUL";
        case OpCode::DIV:        return "DIV";
        case OpCode::RETURN:     return "RETURN";
    }

    throw std::runtime_error("Unknown IR opcode.");
}

std::string IRPrinter::print(
    const std::vector<Instruction>& instructions
) {
    std::ostringstream output;

    output << "Intermediate Representation (IR)\n";
    output << "---------------------------------\n";

    for (const auto& instruction : instructions) {
        output << opcodeToString(instruction.opcode);

        switch (instruction.opcode) {
            case OpCode::LOAD_CONST:
                output << " R" << instruction.destination
                       << ", " << instruction.constant;
                break;

            case OpCode::LOAD:
                output << " R" << instruction.destination
                       << ", " << instruction.name;
                break;

            case OpCode::STORE:
                output << " " << instruction.name
                       << ", R" << instruction.source1;
                break;

            case OpCode::ADD:
            case OpCode::SUB:
            case OpCode::MUL:
            case OpCode::DIV:
                output << " R" << instruction.destination
                       << ", R" << instruction.source1
                       << ", R" << instruction.source2;
                break;

            case OpCode::RETURN:
                output << " R" << instruction.source1;
                break;
        }

        output << '\n';
    }

    return output.str();
}