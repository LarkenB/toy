#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

typedef bool (*_Predicate)(char);

bool _reader_check_condition_or_eof(Reader* reader, _Predicate p) {
	return p(reader_peek(reader)) && !reader->eof; 
}

char* _reader_read_while_condition_or_until_eof(Reader* reader, char first, _Predicate p) {
	int bufSize = 100;
	int index = 0;
	char* buf = malloc(sizeof(char) * bufSize);
	buf[index++] = first;
	if (!buf) return NULL; 

	while (_reader_check_condition_or_eof(reader, p)) {
		char c = reader_next(reader);
		if (index == bufSize) {
			bufSize += 100;
			buf = realloc(buf, bufSize);
			if (!buf) return NULL;
		}

		buf[index++] = c;
	}

	if (index == bufSize) {
		bufSize++;
		buf = realloc(buf, bufSize);
		if (!buf) return NULL;
	}

	buf[index++] = '\0';
	return buf;
}

bool _can_start_id(char c) {
	return isalpha(c) || c == '_';
}

bool _can_be_in_id(char c) {
	return isalnum(c) || c == '_';
}

bool _can_be_in_int(char c) {
	return isdigit(c);
}

Token _lexer_internal_next(Lexer* lex) {
	Reader* reader = lex->reader;

start:
	if (reader->eof) {
		Token tok = { .type = Eof };
		return tok;
	}

	// Skip whitespace
	while (isspace(reader_peek(reader)) && !reader->eof) {
		reader_next(reader);
	}

	if (reader->eof) {
		Token tok = { .type = Eof };
		return tok;
	}

	char c = reader_next(reader);

	// Identifier and Keywords
	if (_can_start_id(c)) {
		char* identifier = _reader_read_while_condition_or_until_eof(reader, c, _can_be_in_id);
		Token tok = { .lexeme = identifier };
		if (strcmp(identifier, "func")) {
			tok.type = Func;
		} else {
			tok.type = Id;
		}
		return tok;
	}

	// Integer Literals
	if (_can_be_in_int(c)) {
		char* literalString = _reader_read_while_condition_or_until_eof(reader, c, _can_be_in_int);
		Token tok = { .type = Int, .lexeme = literalString };
		return tok;
	}

	// Special Chars
	switch (c) {
		case '(': {
			Token tok = { .type = LParen, .lexeme = "(" };
			return tok;
		}
		case ')': {
			Token tok = { .type = LParen, .lexeme = ")" };
			return tok;
		}
		case '{': {
			Token tok = { .type = LBrace, .lexeme = "{" };
			return tok;
		}
		case '}': {
			Token tok = { .type = LBrace, .lexeme = "}" };
			return tok;
		}
		case ';': {
			Token tok = { .type = Semi, .lexeme = ";" };
			return tok;
		}
	}

	// TODO: proper error handling or convert to assert
	Token tok = { .type = Error, .lexeme = "error: invalid char in lexer" };
	return tok;
}

Token lexer_next(Lexer* lex) {
	return _lexer_internal_next(lex);
}

bool lexer_expect(Lexer* lex, TokenType type, Token* tok) {
	Token next = lexer_next(lex);
	if (next.type == type) {
		*tok = next;
		return true;
	}
	tok = NULL;
	return false;
}
