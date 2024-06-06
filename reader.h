#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	FILE* file;
	bool eof;
	char _peeked;
} Reader;

char reader_next(Reader* reader);

char reader_peek(Reader* reader);

