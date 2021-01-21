#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H


const char *doubleToStr( double value );
void cnvtToUpperCase( char *str );
char *trimWhitespace( char *str );
void cnvtChar( char *str, char from, char to );

void ReplaceReservedXmlCharacters(const char *input, char *output );

#endif // PRINT_UTILS_H
