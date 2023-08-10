#include "s21_string.h"

static int is_delim(char c, const char *delim) {
  int i;

  i = 0;
  while (*delim != '\0') {
    if (c == *delim) i = 1;
    delim++;
  }
  return (i);
}

static char *skip_delimeters(char *s, const char *delim) {
  while (1) {
    if (is_delim(*s, delim)) {
      s++;
      continue;
    }
    if (*s == '\0') s = s21_NULL;
    break;
  }
  return (s);
}

char *s21_strtok(char *s, const char *delim) {
  static char *p;
  char *ret;

  if (!s) s = p;
  if (*s == '\0' || !s) {
    ret = s21_NULL;
  } else {
    s = skip_delimeters(s, delim);
    ret = s;
    while (1) {
      if (*s == '\0') {
        p = s;
        break;
      }
      if (is_delim(*s, delim)) {
        *s = '\0';
        p = s + 1;
        break;
      }
      s++;
    }
  }
  return (ret);
}
