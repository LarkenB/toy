#pragma once
#include <stdbool.h>
#include "reader.h"

typedef struct {
	Reader* reader;
} Lexer;

typedef enum {
	Id,
	Int,
	Eof,
	Func,
	Error
} TokenType;

typedef struct {
	TokenType type;
	char* lexeme;
} Token;

Token lexer_next(Lexer* lex);

bool lexer_expect(Lexer* lex, TokenType type, Token* tok);
