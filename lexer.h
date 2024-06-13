#pragma once
#include <stdbool.h>
#include "reader.h"

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

typedef struct {
	Reader* reader;
	Token* _peeked;
} Lexer;

void lexer_init(Lexer* lex, Reader* reader);

Token lexer_next(Lexer* lex);

Token lexer_peek(Lexer* lex);

bool lexer_expect(Lexer* lex, TokenType type, Token* tok);
