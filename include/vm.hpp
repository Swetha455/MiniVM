#ifndef MINIVM_VM_HPP
#define MINIVM_VM_HPP

#include "ir.hpp"

#include <string>
#include <unordered_map>
#include <vector>

class VirtualMachine {
public:
    int execute(const std::vector<Instruction>& instructions);

private:
    std::vector<int> registers;
    std::unordered_map<std::string, int> variables;
};

#endif