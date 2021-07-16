#ifndef TRY_H
#define TRY_H

// Functions preceded by an underline shouldn't be used directly.

FILE * _try_open(char path[], char mode[], char source[], int line, char const function[]);

#define TRY_OPEN(PATHNAME, MODE) _try_open((PATHNAME), (MODE), (__FILE__), (__LINE__), (__func__))

#endif /* TRY_H */
