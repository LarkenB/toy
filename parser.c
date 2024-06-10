#include "parser.h"

void parser_parse_program(Parser* par) {
  Lexer* lex = par->lex;

	Token tok = lexer_next(lex);
	while (tok.type != Eof) {
		printf("%s\n", tok.lexeme);
		tok = lexer_next(lex);
	}
	
	printf("compiled succesfully");

}
