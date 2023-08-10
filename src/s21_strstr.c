#include "s21_string.h"

static char *findstr(const char *str, const char *needle) {
  int i;
  int j;
  int k;
  char *ret;
  char *str1;

  ret = s21_NULL;
  str1 = (char *)str;
  i = 0;
  while (str1[i] != '\0') {
    j = i;
    k = 0;
    while ((str1[j] == needle[k]) && (str1[j] != '\0')) {
      j++;
      k++;
    }
    if (needle[k] == '\0') {
      ret = &str1[i];
      break;
    }
    i++;
  }
  return (ret);
}

char *s21_strstr(const char *str, const char *needle) {
  const char *ret;

  if (s21_strlen(needle) > s21_strlen(str)) ret = s21_NULL;
  if (needle[0] == '\0')
    ret = str;
  else
    ret = findstr(str, needle);
  return ((char *)ret);
}
