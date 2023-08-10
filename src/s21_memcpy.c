#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *buffer = (unsigned char *)dest;
  unsigned char *buffer2 = (unsigned char *)src;
  if (buffer != s21_NULL && buffer2 != s21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      buffer[i] = buffer2[i];
    }
  }
  return buffer;
}
