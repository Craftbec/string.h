#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
int flag = 0;
int i = 0;

while(*(str1 + i) || *(str2 + i)) {
    if (*(str1 + i) != *(str2 + i)) {
        flag = *(str1 + i) - *(str2 + i);
        break;
    }
    i++;
}
return flag;
}
