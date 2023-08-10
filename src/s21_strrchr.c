#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *str_tem = s21_NULL;
  int l = (int)s21_strlen(str);
  for (; l >= 0; l--) {
    if (str[l] == c) {
      str_tem = (char *)&str[l];
      l = -1;
    }
  }
  return str_tem;
}
