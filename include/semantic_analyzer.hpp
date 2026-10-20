#ifndef MINIVM_SEMANTIC_ANALYZER_HPP
#define MINIVM_SEMANTIC_ANALYZER_HPP

#include "ast.hpp"

#include <string>
#include <unordered_set>

class SemanticAnalyzer {
public:
    void analyze(const Program& program);

private:
    std::unordered_set<std::string> declaredVariables;

    void analyzeStatement(const Stmt& statement);
    void analyzeExpression(const Expr& expression);
};

#endif