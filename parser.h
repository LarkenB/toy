#pragma once
#include "lexer.h"
#include "ast.h"

typedef struct {
	Lexer* lex;
} Parser;

ProgramAst parser_parse_program(Parser* par);

FuncAst parser_parse_function(Parser* par);

ParamListAst* parser_parse_param_list(Parser* par);

ParamAst* parser_parse_param(Parser* par);

ExprAst parser_parse_expr(Parser* par);

StmtAst parser_parse_stmt(Parser* par);


