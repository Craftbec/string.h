#include "s21_string.h"


char *s21_strcpy(char *dest, const char *src) {
  s21_size_t i;
  s21_size_t len = s21_strlen(src);
  for (i = 0; i < len; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}
