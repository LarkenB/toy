#include <stdlib.h>
#include "parser.h"

// TODO: change to parser_parse_file and look at supporting multiple files
ProgramAst parser_parse_program(Parser* par) {
  Lexer* lex = par->lex;
	
	Token tok = lexer_peek(lex);
	while (tok.type != Eof) {
		FuncAst function = parser_parse_function(par);
		printf("function: %s\n", function.funcName.lexeme);
		tok = lexer_peek(lex);
	}
	
	printf("compiled succesfully");
  ProgramAst program = {};
	return program; 
}

// FuncAst ::= 'func' 'Id' '(' ParamListAst ')' ('->' TypeAst)? StmtBlockAst
FuncAst parser_parse_function(Parser* par) {
	Lexer* lex = par->lex;

	// Eat 'func'
	Token error;
	if (!lexer_expect(lex, Func, &error)) {
			printf("error: expected \"func\" at start of function definition, but got token of type: %d with lexeme: %s\n", error.type, error.lexeme);
			exit(1);
	}

	// Parse function name
	Token funcName;
	if (!lexer_expect(lex, Id, &funcName)) {
			printf("error: expected fuction name after \"func\"\n");
			exit(1);
	}
	
	// Eat '('
	if (!lexer_expect(lex, LParen, NULL)) {
			printf("error: expected \"(\" after function name\n");
			exit(1);
	}
	
	ParamListAst* params = lexer_peek(lex).type == RParen ? NULL : parser_parse_param_list(par);

	// Eat ')'
	if (!lexer_expect(lex, RParen, NULL)) {
			printf("error: expected \")\" at the end of function parameter list\n");
			exit(1);
	}
	
	// Parse return type (optional)
	if (lexer_peek(lex).type == Arrow) {
		// TODO: split into a parser_parse_type() function
		lexer_next(lex); // Eat '->'
		Token typeName;
		if (!lexer_expect(lex, Id, &typeName)) {
			printf("error: expected return type after \"->\"\n");
			exit(1);
		}
	}
	
	// Eat '{'
	if (!lexer_expect(lex, LBrace, NULL)) {
			printf("error: expected \"{\" at the start of function body\n");
			exit(1);
	}
	
	// Eat '}'
	if (!lexer_expect(lex, RBrace, NULL)) {
			printf("error: expected \"}\" at the end of function body\n");
			exit(1);
	}

	FuncAst function = {
		.funcName = funcName,
		.params = params
	};

	return function;
}

// ParamListAst ::= ParamAst ',' ParamListAst
// 	| ParamAst
ParamListAst* parser_parse_param_list(Parser* par) {
	Lexer* lex = par->lex;

	ParamAst* param = parser_parse_param(par);
	ParamListAst* paramList = malloc(sizeof(ParamListAst));
	paramList->param = param;
	paramList->next = NULL;
	if (lexer_peek(lex).type == Comma) {
		// Eat ','
		lexer_next(lex);
		paramList->next = parser_parse_param_list(par);
	}
	
	return paramList;
}

// ParamAst ::= 'Id' ':' 'Id'
ParamAst* parser_parse_param(Parser* par) {
	Lexer* lex = par->lex;
	
	// Parse parameter name
	Token paramName;
	if (!lexer_expect(lex, Id, &paramName)) {
			printf("error: expected parameter name\n");
			exit(1);
	}

	// Eat ':' 
	if (!lexer_expect(lex, Colon, NULL)) {
		printf("error: expected \":\" after parameter name\n");
		exit(1);
	}

	// Parse parameter type
	Token typeName;
	if (!lexer_expect(lex, Id, &typeName)) {
		printf("error expected type name after \":\"\n");
		exit(1);
	}

	ParamAst* param = malloc(sizeof(ParamAst));
	return param;
}

ExprAst parser_parse_expr(Parser* par) {
	ExprAst expr = {};
	return expr;
}

StmtAst parser_parse_stmt(Parser* par) {
	StmtAst stmt = {};
	return stmt;
}

