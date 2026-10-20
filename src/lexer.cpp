#include "lexer.hpp"

#include <cctype>
#include <utility>

Lexer::Lexer(const std::string& source)
    : source(source) {}

char Lexer::currentChar() const {
    if (position >= source.size()) {
        return '\0';
    }

    return source[position];
}

char Lexer::peekNext() const {
    if (position + 1 >= source.size()) {
        return '\0';
    }

    return source[position + 1];
}

void Lexer::advance() {
    if (currentChar() == '\n') {
        ++line;
    }

    ++position;
}

void Lexer::addToken(TokenType type) {
    tokens.push_back({
        type,
        source.substr(
            tokenStart,
            position - tokenStart
        ),
        line
    });
}

void Lexer::skipWhitespace() {
    while (std::isspace(
        static_cast<unsigned char>(currentChar())
    )) {
        advance();
    }
}

void Lexer::scanNumber() {
    while (std::isdigit(
        static_cast<unsigned char>(currentChar())
    )) {
        advance();
    }

    addToken(TokenType::NUMBER);
}

void Lexer::scanIdentifier() {
    while (
        std::isalnum(
            static_cast<unsigned char>(currentChar())
        ) ||
        currentChar() == '_'
    ) {
        advance();
    }

    std::string text = source.substr(
        tokenStart,
        position - tokenStart
    );

    if (text == "int") {
        addToken(TokenType::INT);
    } else if (text == "return") {
        addToken(TokenType::RETURN);
    } else {
        addToken(TokenType::IDENTIFIER);
    }
}

void Lexer::scanToken() {
    char c = currentChar();

    switch (c) {
        case '(':
            advance();
            addToken(TokenType::LEFT_PAREN);
            break;

        case ')':
            advance();
            addToken(TokenType::RIGHT_PAREN);
            break;

        case '{':
            advance();
            addToken(TokenType::LEFT_BRACE);
            break;

        case '}':
            advance();
            addToken(TokenType::RIGHT_BRACE);
            break;

        case '+':
            advance();
            addToken(TokenType::PLUS);
            break;

        case '-':
            advance();
            addToken(TokenType::MINUS);
            break;

        case '*':
            advance();
            addToken(TokenType::STAR);
            break;

        case '/':
            advance();
            addToken(TokenType::SLASH);
            break;

        case '=':
            advance();
            addToken(TokenType::EQUAL);
            break;

        case ';':
            advance();
            addToken(TokenType::SEMICOLON);
            break;

        default:
            if (std::isdigit(
                static_cast<unsigned char>(c)
            )) {
                scanNumber();
            } else if (
                std::isalpha(
                    static_cast<unsigned char>(c)
                ) ||
                c == '_'
            ) {
                scanIdentifier();
            } else {
                advance();
                addToken(TokenType::INVALID);
            }

            break;
    }
}

std::vector<Token> Lexer::tokenize() {
    while (position < source.size()) {
        skipWhitespace();

        if (position >= source.size()) {
            break;
        }

        tokenStart = position;
        scanToken();
    }

    tokens.push_back({
        TokenType::END_OF_FILE,
        "",
        line
    });

    return tokens;
}