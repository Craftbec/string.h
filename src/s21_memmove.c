#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  unsigned char *buffer = (unsigned char *)dest;
  unsigned char *buffer2 = (unsigned char *)src;
  unsigned char tmp_str[n];
  for (s21_size_t i = 0; i < n; i++) {
    tmp_str[i] = buffer2[i];
  }
  for (s21_size_t i = 0; i < n; i++) {
    buffer[i] = tmp_str[i];
  }
  return buffer;
}
