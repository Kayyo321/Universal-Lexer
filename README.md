# Universal-Lexer
A lexer written in C for you, so you never have to write one again!

## How to use

#### Creating the lexer

Use the struct ```Lexer``` to create a new lexer like this:

```Lexer *lexer = InitLexer(fileContents);```

> InitLexer expects a char array. 

Use the struct ```Token``` to create a new token like this:

```Token *token = NextToken(lexer);```

> NextToken expects a pointer to your lexer object.


To gather all of your tokens, I suggest doing a while-loop:

```
while (curToken->type != NULL_VAL) {
      PrintToken(curToken);

      DeleteToken(curToken);
      curToken = NextToken(lexer);
}
```

> Once the lexer has reached the final token, NextToken will return a token with the type ```NULL_VAL```.
> 
> Calling PrintToken, will print out the token in this format: (Example) "TOKEN: ["main", TYPE: IDENTIFIER, LN: 1]".

Do not forget to call DeleteLexer, and DeleteToken, once you are done using both.

A full implementation of this would be:

```
Lexer *lexer = InitLexer(fileContents);
Token *token = NextToken(lexer);

while (curToken->type != NULL_VAL) {
    PrintToken(curToken);

    DeleteToken(curToken);
    curToken = NextToken(lexer);
}

DeleteLexer(lexer);
```
