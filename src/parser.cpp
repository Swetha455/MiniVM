#include "parser.hpp"

#include <stdexcept>
#include <string>
#include <utility>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens) {}

const Token& Parser::current() const {
    return tokens[position];
}

const Token& Parser::previous() const {
    return tokens[position - 1];
}

bool Parser::check(TokenType type) const {
    return current().type == type;
}

bool Parser::match(TokenType type) {
    if (!check(type)) {
        return false;
    }

    ++position;
    return true;
}

const Token& Parser::consume(
    TokenType type,
    const char* message
) {
    if (check(type)) {
        return tokens[position++];
    }

    throw std::runtime_error(
        std::string("Parser error at line ") +
        std::to_string(current().line) +
        ": " + message
    );
}

Program Parser::parse() {
    return parseProgram();
}

Program Parser::parseProgram() {
    consume(TokenType::INT, "Expected 'int' at program start.");

    const Token& name = consume(
        TokenType::IDENTIFIER,
        "Expected function name."
    );

    if (name.lexeme != "main") {
        throw std::runtime_error(
            "Parser error: Expected function name 'main'."
        );
    }

    consume(TokenType::LEFT_PAREN, "Expected '('.");
    consume(TokenType::RIGHT_PAREN, "Expected ')'.");
    consume(TokenType::LEFT_BRACE, "Expected '{'.");

    Program program;

    while (!check(TokenType::RIGHT_BRACE) &&
           !check(TokenType::END_OF_FILE)) {
        program.statements.push_back(parseStatement());
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}'.");
    consume(TokenType::END_OF_FILE, "Unexpected content after program.");

    return program;
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    if (match(TokenType::INT)) {
        return parseVarDeclaration();
    }

    if (match(TokenType::RETURN)) {
        return parseReturnStatement();
    }

    throw std::runtime_error(
        std::string("Parser error at line ") +
        std::to_string(current().line) +
        ": Expected a statement."
    );
}

std::unique_ptr<Stmt> Parser::parseVarDeclaration() {
    const Token& name = consume(
        TokenType::IDENTIFIER,
        "Expected variable name."
    );

    consume(TokenType::EQUAL, "Expected '=' after variable name.");

    auto initializer = parseExpression();

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after variable declaration."
    );

    return std::make_unique<VarDeclStmt>(
        name.lexeme,
        std::move(initializer)
    );
}

std::unique_ptr<Stmt> Parser::parseReturnStatement() {
    auto value = parseExpression();

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after return expression."
    );

    return std::make_unique<ReturnStmt>(
        std::move(value)
    );
}

std::unique_ptr<Expr> Parser::parseExpression() {
    auto expression = parseTerm();

    while (check(TokenType::PLUS) ||
           check(TokenType::MINUS)) {
        char op = current().lexeme[0];
        ++position;

        auto right = parseTerm();

        expression = std::make_unique<BinaryExpr>(
            op,
            std::move(expression),
            std::move(right)
        );
    }

    return expression;
}

std::unique_ptr<Expr> Parser::parseTerm() {
    auto expression = parseFactor();

    while (check(TokenType::STAR) ||
           check(TokenType::SLASH)) {
        char op = current().lexeme[0];
        ++position;

        auto right = parseFactor();

        expression = std::make_unique<BinaryExpr>(
            op,
            std::move(expression),
            std::move(right)
        );
    }

    return expression;
}

std::unique_ptr<Expr> Parser::parseFactor() {
    if (match(TokenType::NUMBER)) {
        return std::make_unique<NumberExpr>(
            std::stoi(previous().lexeme)
        );
    }

    if (match(TokenType::IDENTIFIER)) {
        return std::make_unique<VariableExpr>(
            previous().lexeme
        );
    }

    if (match(TokenType::LEFT_PAREN)) {
        auto expression = parseExpression();

        consume(
            TokenType::RIGHT_PAREN,
            "Expected ')' after expression."
        );

        return expression;
    }

    throw std::runtime_error(
        std::string("Parser error at line ") +
        std::to_string(current().line) +
        ": Expected an expression."
    );
}