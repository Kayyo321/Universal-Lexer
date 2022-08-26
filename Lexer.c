#include "Lexer.h"

char *AppChar(char *s, char c) {
    int len = strlen(s);
    char buf[len+2];
    strcpy(buf, s);
    buf[len] = c;
    buf[len + 1] = 0;
    return strdup(buf);
}

Token *InitToken(char *_data, enum TokenType _type, size_t _lineNumber) {
    Token *newToken = calloc(1, sizeof(Token));

    newToken->data = _data;
    newToken->type = _type;
    newToken->lineNumber = _lineNumber;

    return newToken;
}

void DeleteToken(Token *token) {
    free(token->data);
    free(token);
}

void PrintToken(Token *token) {
    printf("TOKEN: [\"%s\", TYPE: %s, LN: %d]\n", token->data, tokenTypeStrings[token->type], token->lineNumber);
}

Lexer *InitLexer(char *_data) {
    Lexer *newLexer = calloc(1, sizeof(Lexer));

    newLexer->data = _data;
    newLexer->curPos = 0;
    newLexer->curChar = _data[0];
    newLexer->curLine = 1;

    return newLexer;
}

void DeleteLexer(Lexer *lexer) {
    free(lexer);
}

char Peek(Lexer *lexer) {
    if (lexer->data[lexer->curPos + 1] != '\0') {
        return lexer->data[lexer->curPos + 1];
    }

    return '\0';
}

bool Eat(Lexer *lexer) {
    if ((lexer->curChar = lexer->data[++lexer->curPos]) != '\0') {
        return true;
    }

    return false;
}

Token *NextToken(Lexer *lexer) {
    Token *curTok = InitToken("", NULL_VAL, lexer->curLine);

ReRun:
    if (isalpha(lexer->curChar) || lexer->curChar == '_') {
        curTok->type = IDENTIFIER;

        bool eatenLastChar = true;

        while (isalpha(lexer->curChar) || lexer->curChar == '_') {
            if (!eatenLastChar) {
                break;
            }

            curTok->data = AppChar(curTok->data, lexer->curChar);(curTok->data, lexer->curChar);

            eatenLastChar = Eat(lexer);
        }
    }
    else if (isdigit(lexer->curChar)) {
        if (curTok->type == MAYBE_DOUBLE) {
            curTok->type = DOUBLE_LITERAl;
        }
        else {
            curTok->type = INTEGER_LITERAL;
        }

        bool eatenLastChar = true;

        while (isdigit(lexer->curChar) || lexer->curChar == '.') {
            if (!eatenLastChar) {
                break;
            }

            curTok->data = AppChar(curTok->data, lexer->curChar);

            if (lexer->curChar == '.') {
                if (curTok->type != DOUBLE_LITERAl) {
                    curTok->type = DOUBLE_LITERAl;
                }
            }

            eatenLastChar = Eat(lexer);
        }
    }
    else {
        if (curTok->type == MAYBE_DOUBLE) {
            curTok->type = PERIOD;
            return curTok;
        }

        switch (lexer->curChar) {
            case '\r':
            case '\t':
            case ' ':
                if (Eat(lexer)) {
                    goto ReRun;
                }
                break;

            case '\n':
                curTok->lineNumber = ++lexer->curLine;
                Eat(lexer);
                goto ReRun;

            case '+':
                curTok->type = PLUS;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                if (Peek(lexer) == '+') {
                    curTok->type = PLUS_PLUS;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                else if (Peek(lexer) == '=') {
                    curTok->type = PLUS_EQU;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                break;

            case '-':
                curTok->type = MINUS;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                if (Peek(lexer) == '=') {
                    curTok->type = MINUS_EQU;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                else if (Peek(lexer) == '-') {
                    curTok->type = MINUS_MINUS;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                else if (Peek(lexer) == '>') {
                    curTok->type = R_ARROW;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                break;

            case '*':
                curTok->type = ASTERISK;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case '/':
                curTok->type = DIVIDE;

                if (Peek(lexer) == '/') {
                    while (lexer->curChar != '\n' && lexer->curChar != '\0') {
                        Eat(lexer);
                    }

                    goto ReRun;
                }
                else {
                    curTok->data = AppChar(curTok->data, lexer->curChar);
                }
                break;

            case '%':
                curTok->type = MOD;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case ';':
                curTok->type = SEMICOLON;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case '"':
                curTok->type = STRING_LITERAL;

                Eat(lexer);

                while (lexer->curChar != '"' && lexer->curChar != '\0') {
                    curTok->data = AppChar(curTok->data, lexer->curChar);;
                    Eat(lexer);
                }

                Eat(lexer);
                break;

            case '(':
                curTok->type = L_PARAN;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case ')':
                curTok->type = R_PARAN;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case '[':
                curTok->type = L_BRACKET;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case ']':
                curTok->type = R_BRACKET;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case '{':
                curTok->type = L_CURLY;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case '}':
                curTok->type = R_CURLY;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case '|':
                curTok->type = PIPE;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                if (Peek(lexer) == '|') {
                    curTok->type = OR;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                break;

            case '&':
                curTok->type = REF;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                if (Peek(lexer) == '&') {
                    curTok->type = AND;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                break;

            case ',':
                curTok->type = COMMA;
                curTok->data = AppChar(curTok->data, lexer->curChar);
                break;

            case '.':
                curTok->type = MAYBE_DOUBLE;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                Eat(lexer);

                goto ReRun;

            case '=':
                curTok->type = EQU;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                if (Peek(lexer) == '=') {
                    curTok->type = EQU_EQU;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                break;

            case '<':
                curTok->type = LT;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                if (Peek(lexer) == '=') {
                    curTok->type = LT_EQU;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                else if (Peek(lexer) == '-') {
                    curTok->type = L_ARROW;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                break;

            case '>':
                curTok->type = GT;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                if (Peek(lexer) == '=') {
                    curTok->type = GT_EQU;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                break;

            case '!':
                curTok->type = NOT;
                curTok->data = AppChar(curTok->data, lexer->curChar);

                if (Peek(lexer) == '=') {
                    curTok->type = NOT_EQU;
                    curTok->data = AppChar(curTok->data, Peek(lexer));
                    Eat(lexer);
                }
                break;

            default: break;
        }

        Eat(lexer);

        return curTok;
    }

    return curTok;
}
