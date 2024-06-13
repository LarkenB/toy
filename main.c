#include <stdio.h>
#include "reader.h"
#include "lexer.h"
#include "parser.h"

int main() {
	
	FILE* file = fopen("example.toy", "r");

	Reader reader = { .file = file };
	Lexer lex;
	lexer_init(&lex, &reader);
	Parser par = { .lex = &lex };

	parser_parse_program(&par);

	return 0;
}
