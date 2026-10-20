#ifndef MINIVM_IR_HPP
#define MINIVM_IR_HPP

#include <string>
#include <vector>
#include "ast.hpp"

enum class OpCode {
    LOAD_CONST,
    LOAD,
    STORE,
    ADD,
    SUB,
    MUL,
    DIV,
    RETURN
};

struct Instruction {
    OpCode opcode;

    int destination = -1;
    int source1 = -1;
    int source2 = -1;

    int constant = 0;
    std::string name;
};

class IRGenerator {
public:
    std::vector<Instruction> generate(const Program& program);

private:
    std::vector<Instruction> instructions;
    int nextRegister = 0;

    int allocateRegister();

    int emitConstant(int value);
    int emitLoad(const std::string& name);
    void emitStore(const std::string& name, int source);
    int emitBinary(OpCode opcode, int left, int right);
    void emitReturn(int source);
    int generateExpression(const Expr& expression);
    void generateStatement(const Stmt& statement);
};

#endif