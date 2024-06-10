#pragma once
#include "lexer.h"

typedef struct {
	Lexer* lex;
} Parser;

void parser_parse_program(Parser* par);
