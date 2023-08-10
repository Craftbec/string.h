#include <stdlib.h>

#include "s21_string.h"

char *s21_instr(int n) {
  char str[12];
  char *out;
  int i, j, minus;
  i = 0;
  j = 0;
  minus = 0;
  if (n == -2147483648) {
    n /= 10;
    str[i++] = 8 + '0';
  }
  if (n < 0) {
    n *= -1;
    minus++;
  }
  while (n) {
    str[i++] = n % 10 + '0';
    n /= 10;
  }
  if (minus) {
    str[i++] = '-';
  }
  out = (char *)malloc(sizeof(char) * (i + 1));
  while (i--) {
    out[j++] = str[i];
  }
  out[j] = '\0';
  return (out);
}
char *s21_concat(char *str1, char *str2) {
  char *out = str1;
  while (*str1) {
    str1++;
  }
  while (*str2) {
    *str1++ = *str2++;
  }
  *str1 = '\0';
  return (out);
}

char *s21_strerror(int errnum) {
  char *res_itoa;
  char *res = s21_NULL;
#if __linux__
  char *str[135] = LINUX;
  if (errnum >= 0 && errnum <= 133) {
    res = str[errnum];
  } else {
    char out[2048] = "Unknown error ";
    res_itoa = s21_instr(errnum);
    res = s21_concat(out, res_itoa);
    free(res_itoa);
  }
#elif __APPLE__
  char *mac[108] = APPLE;
  if (errnum >= 0 && errnum <= 106) {
    res = mac[errnum];
  } else {
    char out[2048] = "Unknown error: ";
    res_itoa = s21_instr(errnum);
    res = s21_concat(out, res_itoa);
    free(res_itoa);
  }
#endif
  return (res);
}
