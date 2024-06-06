#include "reader.h"

char _reader_internal_next(Reader* reader) {
	int c = fgetc(reader->file);
	reader->eof = c == EOF;
	return (char)c;
}

char reader_next(Reader* reader) {
	if (reader->_peeked) {
		char c = reader->_peeked;
		reader->_peeked = 0;
		return c;
	}
	return _reader_internal_next(reader);
}

char reader_peek(Reader* reader) {
	if (reader->_peeked) {
		return reader->_peeked;
	}
  reader->_peeked = _reader_internal_next(reader);
	return reader->_peeked;
}
