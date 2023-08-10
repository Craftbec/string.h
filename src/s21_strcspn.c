#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  char *out2;
  s21_size_t i, j;
  int flag = -1;

  out2 = (char *)str2;
  i = 0;
  while (*str1) {
    j = 0;
    while (out2[j]) {
      if (*str1 == out2[j]) {
        flag = i;
        break;
      }
      j++;
    }
    if (flag != -1) {
      break;
    }
    str1++;
    i++;
  }
  return (i);
}
