#ifndef MINIVM_AST_HPP
#define MINIVM_AST_HPP

#include <memory>
#include <string>
#include <vector>

// Base class for all expressions
struct Expr {
    virtual ~Expr() = default;
};

// Represents an integer literal, such as 10 or 25
struct NumberExpr : Expr {
    int value;

    explicit NumberExpr(int value)
        : value(value) {}
};

// Represents a variable reference, such as a or total
struct VariableExpr : Expr {
    std::string name;

    explicit VariableExpr(std::string name)
        : name(std::move(name)) {}
};

// Represents a binary expression, such as a + b
struct BinaryExpr : Expr {
    char op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(
        char op,
        std::unique_ptr<Expr> left,
        std::unique_ptr<Expr> right
    )
        : op(op),
          left(std::move(left)),
          right(std::move(right)) {}
};

// Base class for statements
struct Stmt {
    virtual ~Stmt() = default;
};

// Represents a variable declaration, such as int a = 10;
struct VarDeclStmt : Stmt {
    std::string name;
    std::unique_ptr<Expr> initializer;

    VarDeclStmt(
        std::string name,
        std::unique_ptr<Expr> initializer
    )
        : name(std::move(name)),
          initializer(std::move(initializer)) {}
};

// Represents a return statement, such as return a + 10;
struct ReturnStmt : Stmt {
    std::unique_ptr<Expr> value;

    explicit ReturnStmt(std::unique_ptr<Expr> value)
        : value(std::move(value)) {}
};

// Represents the complete program body
struct Program {
    std::vector<std::unique_ptr<Stmt>> statements;
};

#endif