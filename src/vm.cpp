#include "vm.hpp"

#include <stdexcept>

int VirtualMachine::execute(
    const std::vector<Instruction>& instructions
) {
    registers.clear();
    variables.clear();

    auto ensureRegister = [this](int index) {
        if (index < 0) {
            throw std::runtime_error("Invalid register index.");
        }

        if (static_cast<std::size_t>(index) >= registers.size()) {
            registers.resize(static_cast<std::size_t>(index) + 1);
        }
    };

    for (const Instruction& instruction : instructions) {
        switch (instruction.opcode) {
            case OpCode::LOAD_CONST: {
                ensureRegister(instruction.destination);

                registers[instruction.destination] =
                    instruction.constant;

                break;
            }

            case OpCode::LOAD: {
                auto it = variables.find(instruction.name);

                if (it == variables.end()) {
                    throw std::runtime_error(
                        "Undefined variable: " + instruction.name
                    );
                }

                ensureRegister(instruction.destination);

                registers[instruction.destination] = it->second;

                break;
            }

            case OpCode::STORE: {
                ensureRegister(instruction.source1);

                variables[instruction.name] =
                    registers[instruction.source1];

                break;
            }

            case OpCode::ADD:
            case OpCode::SUB:
            case OpCode::MUL:
            case OpCode::DIV: {
                ensureRegister(instruction.source1);
                ensureRegister(instruction.source2);
                ensureRegister(instruction.destination);

                int left = registers[instruction.source1];
                int right = registers[instruction.source2];
                int result = 0;

                switch (instruction.opcode) {
                    case OpCode::ADD:
                        result = left + right;
                        break;

                    case OpCode::SUB:
                        result = left - right;
                        break;

                    case OpCode::MUL:
                        result = left * right;
                        break;

                    case OpCode::DIV:
                        if (right == 0) {
                            throw std::runtime_error(
                                "Division by zero."
                            );
                        }

                        if (left == (-2147483647 - 1) && right == -1) {
                            throw std::runtime_error(
                                "Integer overflow during division."
                            );
                        }

                        result = left / right;
                        break;

                    default:
                        break;
                }

                registers[instruction.destination] = result;

                break;
            }

            case OpCode::RETURN: {
                ensureRegister(instruction.source1);

                return registers[instruction.source1];
            }
        }
    }

    throw std::runtime_error(
        "Program finished without a RETURN instruction."
    );
}