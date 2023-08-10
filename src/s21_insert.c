#include <stdlib.h>

#include "s21_string.h"

void* s21_insert(const char *src, const char *str, size_t start_index) {
    char* out = s21_NULL;
    if (src && str && s21_strlen(src) >= start_index) {
        out = malloc((s21_strlen(src)+s21_strlen(str)+1)*sizeof(char));
        if (out) {
            s21_strncpy(out, src, start_index);
            *(out + start_index) = '\0';
            s21_strcat(out, str);
            s21_strcat(out, src + start_index);
        }
    }
    return out;
}
