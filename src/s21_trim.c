#include <stdlib.h>
#include "s21_string.h"

static s21_size_t s21_strlcpy(char *dest, const char *src, s21_size_t size) {
    s21_size_t i;

    i = 0;
    while (size > 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
        size--;
    }
    if (size != 0)
        dest[i] = '\0';
    while (src[i] != '\0')
        i++;
    return (i);
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *result;
    char *s2;
    s21_size_t start;
    s21_size_t end;
    s21_size_t buf_size;

    s2 = (char *)src;
    result = 0;
    if (src != 0 && trim_chars != 0) {
        start = 0;
        end = s21_strlen(src);
        while (src[start] && s21_strchr(trim_chars, src[start]))
            ++start;
        while (src[end - 1] && s21_strchr(trim_chars, src[end - 1]) && end > start)
            --end;
        buf_size = end - start + 1;
        result = (char *)malloc(sizeof(char) * (buf_size));
        if (result)
            s21_strlcpy(result, &s2[start], (buf_size));
    }
    return (result);
}
