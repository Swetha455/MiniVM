#include "ir.hpp"
#include "ast.hpp"

#include <stdexcept>
#include <utility>

int IRGenerator::allocateRegister() {
    return nextRegister++;
}

int IRGenerator::emitConstant(int value) {
    int destination = allocateRegister();

    Instruction instruction{};
    instruction.opcode = OpCode::LOAD_CONST;
    instruction.destination = destination;
    instruction.constant = value;

    instructions.push_back(instruction);

    return destination;
}

int IRGenerator::emitLoad(const std::string& name) {
    int destination = allocateRegister();

    Instruction instruction{};
    instruction.opcode = OpCode::LOAD;
    instruction.destination = destination;
    instruction.name = name;

    instructions.push_back(instruction);

    return destination;
}

void IRGenerator::emitStore(
    const std::string& name,
    int source
) {
    Instruction instruction{};
    instruction.opcode = OpCode::STORE;
    instruction.source1 = source;
    instruction.name = name;

    instructions.push_back(instruction);
}

int IRGenerator::emitBinary(
    OpCode opcode,
    int left,
    int right
) {
    int destination = allocateRegister();

    Instruction instruction{};
    instruction.opcode = opcode;
    instruction.destination = destination;
    instruction.source1 = left;
    instruction.source2 = right;

    instructions.push_back(instruction);

    return destination;
}

void IRGenerator::emitReturn(int source) {
    Instruction instruction{};
    instruction.opcode = OpCode::RETURN;
    instruction.source1 = source;

    instructions.push_back(instruction);
}

int IRGenerator::generateExpression(const Expr& expression) {
    if (const auto* number =
            dynamic_cast<const NumberExpr*>(&expression)) {
        return emitConstant(number->value);
    }

    if (const auto* variable =
            dynamic_cast<const VariableExpr*>(&expression)) {
        return emitLoad(variable->name);
    }

    if (const auto* binary =
            dynamic_cast<const BinaryExpr*>(&expression)) {
        int left = generateExpression(*binary->left);
        int right = generateExpression(*binary->right);

        OpCode opcode;

        switch (binary->op) {
            case '+':
                opcode = OpCode::ADD;
                break;

            case '-':
                opcode = OpCode::SUB;
                break;

            case '*':
                opcode = OpCode::MUL;
                break;

            case '/':
                opcode = OpCode::DIV;
                break;

            default:
                throw std::runtime_error(
                    "Unsupported binary operator."
                );
        }

        return emitBinary(opcode, left, right);
    }

    throw std::runtime_error("Unsupported expression type.");
}

void IRGenerator::generateStatement(const Stmt& statement) {
    if (const auto* declaration =
            dynamic_cast<const VarDeclStmt*>(&statement)) {
        int value = generateExpression(*declaration->initializer);

        emitStore(declaration->name, value);
        return;
    }

    if (const auto* returnStatement =
            dynamic_cast<const ReturnStmt*>(&statement)) {
        int value = generateExpression(*returnStatement->value);

        emitReturn(value);
        return;
    }

    throw std::runtime_error("Unsupported statement type.");
}

std::vector<Instruction> IRGenerator::generate(
    const Program& program
) {
    instructions.clear();
    nextRegister = 0;

    for (const auto& statement : program.statements) {
        generateStatement(*statement);
    }

    return instructions;
}