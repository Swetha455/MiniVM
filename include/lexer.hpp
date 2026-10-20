#ifndef MINIVM_LEXER_HPP
#define MINIVM_LEXER_HPP

#include <string>
#include <vector>

enum class TokenType {
    INT,
    RETURN,
    IDENTIFIER,
    NUMBER,

    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,

    PLUS,
    MINUS,
    STAR,
    SLASH,

    EQUAL,
    SEMICOLON,

    END_OF_FILE,
    INVALID
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

class Lexer {
public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();

private:
    std::string source;
    std::vector<Token> tokens;

    std::size_t position = 0;
    std::size_t tokenStart = 0;
    int line = 1;

    char currentChar() const;
    char peekNext() const;
    void advance();

    void skipWhitespace();
    void scanToken();
    void scanNumber();
    void scanIdentifier();

    void addToken(TokenType type);
};

#endif