#ifndef MINIVM_PARSER_HPP
#define MINIVM_PARSER_HPP

#include "ast.hpp"
#include "lexer.hpp"

#include <memory>
#include <vector>

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    Program parse();

private:
    const std::vector<Token>& tokens;
    std::size_t position = 0;

    const Token& current() const;
    const Token& previous() const;

    bool check(TokenType type) const;
    bool match(TokenType type);
    const Token& consume(
        TokenType type,
        const char* message
    );

    Program parseProgram();
    std::unique_ptr<Stmt> parseStatement();
    std::unique_ptr<Stmt> parseVarDeclaration();
    std::unique_ptr<Stmt> parseReturnStatement();

    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
};

#endif