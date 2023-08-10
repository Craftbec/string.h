#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  char *buffer;
  buffer = (char *)str;
  if (str != s21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      buffer[i] = c;
    }
  }
  return str;
}
