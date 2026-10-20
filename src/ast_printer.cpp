#include "ast_printer.hpp"

#include <sstream>
#include <stdexcept>

std::string ASTPrinter::print(const Program& program) {
    std::ostringstream output;

    output << "Program\n";

    for (const auto& statement : program.statements) {
        output << "  " << printStatement(*statement) << "\n";
    }

    return output.str();
}

std::string ASTPrinter::printStatement(const Stmt& statement) {
    std::ostringstream output;

    if (const auto* declaration =
            dynamic_cast<const VarDeclStmt*>(&statement)) {
        output << "VariableDeclaration("
               << declaration->name << ", "
               << printExpression(*declaration->initializer)
               << ")";
    }
    else if (const auto* returnStatement =
                 dynamic_cast<const ReturnStmt*>(&statement)) {
        output << "Return("
               << printExpression(*returnStatement->value)
               << ")";
    }
    else {
        throw std::runtime_error("Unknown statement type.");
    }

    return output.str();
}

std::string ASTPrinter::printExpression(const Expr& expression) {
    std::ostringstream output;

    if (const auto* number = dynamic_cast<const NumberExpr*>(&expression)) {
        output << number->value;
    }
    else if (const auto* variable =
                 dynamic_cast<const VariableExpr*>(&expression)) {
        output << "Variable(" << variable->name << ")";
    }
    else if (const auto* binary =
                 dynamic_cast<const BinaryExpr*>(&expression)) {
        output << "("
               << printExpression(*binary->left)
               << " " << binary->op << " "
               << printExpression(*binary->right)
               << ")";
    }
    else {
        throw std::runtime_error("Unknown expression type.");
    }

    return output.str();
}