#ifndef UNIVERSAL_LEXER_LEXER_H
#define UNIVERSAL_LEXER_LEXER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

char *AppChar(char *s, char c);

enum TokenType {
    IDENTIFIER,
    STRING_LITERAL,
    INTEGER_LITERAL,
    MAYBE_DOUBLE,
    DOUBLE_LITERAl,
    PLUS,
    MINUS,
    ASTERISK,
    DIVIDE,
    MOD,
    L_PARAN,
    R_PARAN,
    L_BRACKET,
    R_BRACKET,
    L_CURLY,
    R_CURLY,
    PIPE,
    OR,
    REF,
    AND,
    COMMA,
    PERIOD,
    EQU,
    PLUS_PLUS,
    LT,
    GT,
    LT_EQU,
    GT_EQU,
    L_ARROW,
    R_ARROW,
    PLUS_EQU,
    MINUS_EQU,
    EQU_EQU,
    NOT,
    NOT_EQU,
    SEMICOLON,
    NULL_VAL
};

static const char *tokenTypeStrings[] = {
    "IDENTIFIER",
    "STRING_LITERAL",
    "INTEGER_LITERAL",
    "MAYBE_DOUBLE",
    "DOUBLE_LITERAl",
    "PLUS",
    "MINUS",
    "ASTERISK",
    "DIVIDE",
    "MOD",
    "L_PARAN",
    "R_PARAN",
    "L_BRACKET",
    "R_BRACKET",
    "L_CURLY",
    "R_CURLY",
    "PIPE",
    "OR",
    "REF",
    "AND",
    "COMMA",
    "PERIOD",
    "EQU",
    "PLUS_PLUS",
    "LT",
    "GT",
    "LT_EQU",
    "GT_EQU",
    "L_ARROW",
    "R_ARROW",
    "PLUS_EQU",
    "MINUS_EQU",
    "EQU_EQU",
    "NOT",
    "NOT_EQU",
    "SEMICOLON",
    "NULL_VAL"
};

typedef struct TOKEN_STRUCT {
    char *data;
    enum TokenType type;
    size_t lineNumber;
} Token;

Token *InitToken(char *_data, enum TokenType _type, size_t _lineNumber);
void DeleteToken(Token *token);
void PrintToken(Token *token);

typedef struct LEXER_STRUCT {
    char *data;
    char curChar;
    size_t curPos, curLine;
} Lexer;

Lexer *InitLexer(char *_data);
void DeleteLexer(Lexer *lexer);

char Peek(Lexer *lexer);
bool Eat(Lexer *lexer);

Token *NextToken(Lexer *lexer);

#endif //UNIVERSAL_LEXER_LEXER_H