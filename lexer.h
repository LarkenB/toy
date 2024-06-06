#pragma once
#include <stdbool.h>
#include "reader.h"

typedef struct {
	Reader* reader;
} Lexer;

typedef enum {
	Error,
	Id,
	Int,
	Eof,
	Func,
	LParen,
	RParen,
	LBrace,
	RBrace,
	Semi
} TokenType;

typedef struct {
	TokenType type;
	char* lexeme;
} Token;

Token lexer_next(Lexer* lex);

bool lexer_expect(Lexer* lex, TokenType type, Token* tok);
