#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
char *buffer;
buffer = (char *) dest;
while(*buffer != '\0') {
    buffer++;
}
while (*src != '\0') {
    *buffer++ = *src++;
}
    *buffer ='\0';

return dest;
}
