#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
char *buffer;
buffer = (char *) dest;
while(*buffer != '\0') {
    buffer++;
}
for ( s21_size_t i =0; i < n; i++ ) {
    *buffer++ = *src++;
}
    *buffer ='\0';
return dest;
}
