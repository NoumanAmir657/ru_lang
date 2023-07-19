#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct scanner {
    const char* start;
    const char* current;
    int line;
} Scanner;

Scanner scanner;

// helpers

static bool isAtEnd() {
    return *scanner.current == '\0';
}

static char advance() {
    scanner.current++;
    return scanner.current[-1]; // scanner.current = scanner.current - 1
}

static char peek() {
    return *scanner.current;
}

static char peekNext() {
    if (isAtEnd()) return '\0';
    return scanner.current[1];
}

static bool match(char expected) {
    if (isAtEnd()) return false;
    if (*scanner.current != expected) return false;

    scanner.current++;
    return true;
}

static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

static bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;

    return token;
}

static Token errorToken(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;

    return token;
}

static TokenType checkKeyword(int start, int length, const char* rest, TokenType type) {
    // check for length and whether string match or not
    if (scanner.current - scanner.start == start + length && memcmp(scanner.start + start, rest, length) == 0) {
        return type;
    }

    return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
    // trie of keywords
    switch (scanner.start[0]) {
        case 'a': {
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'g': return checkKeyword(2, 1, "r", TOKEN_IF);
                    case 'n': return checkKeyword(2, 1, "d", TOKEN_AND);
                }
            }
            break;
        }

        case 'e': return checkKeyword(1, 4, "laan", TOKEN_VAR);

        case 'k': return checkKeyword(1, 5, "haaka", TOKEN_CLASS);
        case 'n': return checkKeyword(1, 2, "il", TOKEN_NIL);
        case 'o': return checkKeyword(1, 1, "r", TOKEN_OR);
        case 'c': return checkKeyword(1, 5, "hhaap", TOKEN_PRINT);
        case 'l': return checkKeyword(1, 6, "autana", TOKEN_RETURN);

        case 's': {
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'u': return checkKeyword(2, 3, "per", TOKEN_SUPER);
                    case 'h': return checkKeyword(2, 3, "oro", TOKEN_FOR);
                }
            }
            break;
        }

        case 'j': return checkKeyword(1, 3, "btk", TOKEN_WHILE);
        case 'w': return checkKeyword(1, 4, "arna", TOKEN_ELSE);

        case 'f':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'a': return checkKeyword(2, 3, "lse", TOKEN_FALSE);
                }
            }
            break;

        case 't':
            if (scanner.current - scanner.start > 1) {
                switch (scanner.start[1]) {
                    case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
                    case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
                    case 'a': return checkKeyword(2, 5, "faaul", TOKEN_FUN);
                }
            }
            break;
        }

    return TOKEN_IDENTIFIER;
}

static void skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                scanner.line++;
                advance();
                break;
            case '/':
                if (peekNext() == '/') {
                    // A comment goes until the end of the line.
                    while (peek() != '\n' && !isAtEnd()) advance();
                } 
                else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

static Token string() {
    while(peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') scanner.line++;
        advance();
    }

    if (isAtEnd()) return errorToken("Unterminated string.");

    // the closing quote
    advance();
    return makeToken(TOKEN_STRING);
}

static Token number() {
    while(isDigit(peek())) advance();

    // fractional part if any
    if (peek() == '.' && isDigit(peekNext())) {
        // consume '.'
        advance();
        while(isDigit(peek())) advance();
    }

    return makeToken(TOKEN_NUMBER);
}

static Token identifier() {
    while (isAlpha(peek()) || isDigit(peek())) advance();

    return makeToken(identifierType());
}

void initScanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

// will scan one token at a call
Token scanToken() {
    skipWhitespace();                           // skips whitespaces
    
    scanner.start = scanner.current;            // set start to current

    if (isAtEnd()) return makeToken(TOKEN_EOF); // reached end of file

    char c = advance();                         // get char
 
    if (isAlpha(c)) return identifier();        // checks for identifier or keywords
    if (isDigit(c)) return number();            // check for numbers here instead of in switch case

    switch (c) {
        // 1 char tokens
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case ',': return makeToken(TOKEN_COMMA);
        case '.': return makeToken(TOKEN_DOT);
        case '+': return makeToken(TOKEN_PLUS);
        case '/': return makeToken(TOKEN_SLASH);
        case '*': return makeToken(TOKEN_STAR);

        // 2 char tokens
        case '!':
        return makeToken(
        match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        
        case '=': {
            if (match('=')) {
                return makeToken(TOKEN_EQUAL_EQUAL);
            }
            else {
                return errorToken("Unexpected character.");
            }
        }
        
        case '<': {
            if (match('=')) {
                return makeToken(TOKEN_LESS_EQUAL);
            }
            else if (match('-')) {
                return makeToken(TOKEN_EQUAL);
            }
            else {
                return makeToken(TOKEN_LESS);
            }
        }
        
        case '>':
        return makeToken(
        match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '-':
        return makeToken(
        match('>') ? TOKEN_INHERIT : TOKEN_MINUS);

        // strings
        case '"': return string();
    }
    

    return errorToken("Unexpected character.");
}