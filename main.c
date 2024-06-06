#include <stdio.h>
#include "reader.h"
#include "lexer.h"

int main() {
	
	FILE* file = fopen("example.toy", "r");

	Reader reader = { .file = file };

	Lexer lex = { .reader = &reader };
	
	Token tok = lexer_next(&lex);
	while (tok.type != Eof) {
		printf("%s\n", tok.lexeme);
		tok = lexer_next(&lex);
	}
	
	printf("compiled succesfully");

	return 0;
}
