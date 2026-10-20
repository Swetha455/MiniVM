#include "semantic_analyzer.hpp"

#include <stdexcept>
#include <string>

void SemanticAnalyzer::analyze(const Program& program) {
    declaredVariables.clear();

    for (const auto& statement : program.statements) {
        analyzeStatement(*statement);
    }
}

void SemanticAnalyzer::analyzeStatement(const Stmt& statement) {
    if (const auto* declaration =
            dynamic_cast<const VarDeclStmt*>(&statement)) {

        if (declaredVariables.count(declaration->name) > 0) {
            throw std::runtime_error(
                "Semantic error: Variable '" +
                declaration->name +
                "' has already been declared."
            );
        }

        analyzeExpression(*declaration->initializer);

        declaredVariables.insert(declaration->name);
        return;
    }

    if (const auto* returnStatement =
            dynamic_cast<const ReturnStmt*>(&statement)) {

        analyzeExpression(*returnStatement->value);
        return;
    }

    throw std::runtime_error(
        "Semantic error: Unsupported statement type."
    );
}

void SemanticAnalyzer::analyzeExpression(const Expr& expression) {
    if (dynamic_cast<const NumberExpr*>(&expression)) {
        return;
    }

    if (const auto* variable =
            dynamic_cast<const VariableExpr*>(&expression)) {

        if (declaredVariables.count(variable->name) == 0) {
            throw std::runtime_error(
                "Semantic error: Variable '" +
                variable->name +
                "' was used before being declared."
            );
        }

        return;
    }

    if (const auto* binary =
            dynamic_cast<const BinaryExpr*>(&expression)) {

        analyzeExpression(*binary->left);
        analyzeExpression(*binary->right);
        return;
    }

    throw std::runtime_error(
        "Semantic error: Unsupported expression type."
    );
}