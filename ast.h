#pragma once
#include "lexer.h"

typedef struct {
} ProgramAst;


typedef struct {
	Token paramName;
	Token typeName;
} ParamAst;

typedef struct ParamListAst {
	ParamAst* param;
	struct ParamListAst* next;
} ParamListAst;

typedef struct {
	Token funcName;
	ParamListAst* params;
} FuncAst;

typedef struct {
} ExprAst;

typedef struct {
} StmtAst;
