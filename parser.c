#include <stdlib.h>
#include "parser.h"

ProgramAst parser_parse_program(Parser* par) {
  Lexer* lex = par->lex;
	
	Token tok = lexer_peek(lex);
	while (tok.type != Eof) {
		FunctionAst function = parser_parse_function(par);
		printf("function: %s\n", function.name.lexeme);
		tok = lexer_peek(lex);
	}
	
	printf("compiled succesfully");
  ProgramAst program = {};
	return program; 
}

FunctionAst parser_parse_function(Parser* par) {
	Lexer* lex = par->lex;
	
	Token error;
	if (!lexer_expect(lex, Func, &error)) {
			printf("error: expected \"func\" at start of function definition, but got token of type: %d with lexeme: %s\n", error.type, error.lexeme);
			exit(1);
	}
	
	Token name;
	if (!lexer_expect(lex, Id, &name)) {
			printf("error: expected fuction name after \"func\"\n");
			exit(1);
	}

	if (!lexer_expect(lex, LParen, NULL)) {
			printf("error: expected \"(\" after function name\n");
			exit(1);
	}

	if (!lexer_expect(lex, RParen, NULL)) {
			printf("error: expected \")\" at the end of function parameter list\n");
			exit(1);
	}

	if (!lexer_expect(lex, LBrace, NULL)) {
			printf("error: expected \"{\" at the start of function body\n");
			exit(1);
	}

	if (!lexer_expect(lex, RBrace, NULL)) {
			printf("error: expected \"}\" at the end of function body\n");
			exit(1);
	}

	FunctionAst function = {
		name = name,
	};

	return function;
}

ExprAst parser_parse_expr(Parser* par) {
	ExprAst expr = {};
	return expr;
}

StmtAst parser_parse_stmt(Parser* par) {
	StmtAst stmt = {};
	return stmt;
}

