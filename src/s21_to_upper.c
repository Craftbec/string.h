#include <stdlib.h>

#include "s21_string.h"

void* s21_to_upper(const char* str) {
  char* out = s21_NULL;
  if (str) {
    out = (char*)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (out) {
      s21_strcpy(out, str);
      for (char* str1 = out; *str1; str1++) {
        if (*str1 >= 'a' && *str1 <= 'z') {
          *str1 -= 32;
        }
      }
    }
  }
  return out;
}
