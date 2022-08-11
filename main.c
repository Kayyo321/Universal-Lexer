#include <stdio.h>
#include <stdlib.h>

#include "Lexer.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Incorrect usage:\n");

        for (size_t i = 0; i < argc; ++i) {
            printf("\targv[%d]: %s\n", i, argv[i]);
        }
        return 1;
    }

    char *buffer = 0;
    long length;
    FILE *file = fopen(argv[1], "rb");

    if (!file) {
        printf("Couldn't open file: %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(length);

    if (buffer) {
        fread(buffer, 1, length, file);
    }

    fclose (file);

    Lexer *lexer = InitLexer(buffer);
    Token *curToken = NextToken(lexer);

    while (curToken->type != NULL_VAL) {
        PrintToken(curToken);

        DeleteToken(curToken);
        curToken = NextToken(lexer);
    }

    DeleteLexer(lexer);
    free(buffer);

    return 0;
}