#pragma once
#include "lexer.h"
#include "ast.h"

typedef struct {
	Lexer* lex;
} Parser;

ProgramAst parser_parse_program(Parser* par);

FunctionAst parser_parse_function(Parser* par);

ExprAst parser_parse_expr(Parser* par);

StmtAst parser_parse_stmt(Parser* par);


