#ifndef MINIVM_AST_PRINTER_HPP
#define MINIVM_AST_PRINTER_HPP

#include "ast.hpp"

#include <string>

class ASTPrinter {
public:
    std::string print(const Program& program);

private:
    std::string printStatement(const Stmt& statement);
    std::string printExpression(const Expr& expression);
};

#endif