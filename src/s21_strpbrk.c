#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *out2, *out;
  int i, j;

  out = s21_NULL;
  i = 0;
  out2 = (char *)str2;
  while (*str1) {
    j = 0;
    while (out2[j]) {
      if (*str1 == out2[j]) {
        out = (char *)str1;
        break;
      }
      j++;
    }
    if (out) {
      break;
    }
    str1++;
    i++;
  }
  return (out);
}
