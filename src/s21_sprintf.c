#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

char *s21_itoa(long long num);
void s21_reverse_array(char *a, int n);
char *s21_mixing(char *str, int len);
char *s21_u(long long num);
char *s21_hu(int num);
char *s21_lu(unsigned long num);
char *s21_float(long double num, int n);
void s21_clear(char *str);
void Zero(struct format_sprintf *f);
int specifier(char ch);
int number(char ch);
int parsing(const char **format, struct format_sprintf *flag);
void analysis(const char **format, char **str, struct format_sprintf *ff,
              va_list vl);

int s21_sprintf(char *str, const char *format, ...) {
  char *pmp;
  pmp = str;
  va_list vl;
  va_start(vl, format);
  while (*format) {
    if (*format != '%') {
      *str = *format;
      str++;
      format++;
    } else {
      format++;
      struct format_sprintf struct_f;
      Zero(&struct_f);

      if (parsing(&format, &struct_f) == 1) {
        analysis(&format, &str, &struct_f, vl);
      }
    }
  }
  va_end(vl);
  *str = '\0';
  int l = s21_strlen(pmp);
  return l;
}

void analysis(const char **format, char **str, struct format_sprintf *ff,
              va_list vl) {
  if (**format == 'c') {
    char chr_str = ff->length_l ? va_arg(vl, long int) : va_arg(vl, int);
    if (ff->flag_minus) {
      **str = chr_str;
      (*str)++;
    }
    for (int i = 1; i < ff->width; i++) {
      **str = ' ';
      (*str)++;
    }
    if (!ff->flag_minus) {
      **str = chr_str;
      (*str)++;
    }
    (*format)++;
  } else if (**format == '%') {
    if (ff->flag_minus) {
      **str = '%';
      (*str)++;
    }
    for (int i = 1; i < ff->width; i++) {
      **str = ' ';
      (*str)++;
    }
    if (!ff->flag_minus) {
      **str = '%';
      (*str)++;
    }
    (*format)++;
  } else if (**format == 'd' || **format == 'i') {
    char *str_temp = NULL;
    char str_res[1024] = {0};
    int mixing = 0;
    if (ff->length_l) {
      long int long_tmp;
      long_tmp = va_arg(vl, long int);
      str_temp = s21_itoa(long_tmp);
    } else if (ff->length_h) {
      short int short_tmp;
      short_tmp = (short)va_arg(vl, int);
      str_temp = s21_itoa(short_tmp);
    } else {
      int tmp;
      tmp = va_arg(vl, int);
      str_temp = s21_itoa(tmp);
    }
    int len = s21_strlen(str_temp);
    int res_len = len;
    if ((ff->precision_point) && (str_temp[0] == 48) && (ff->precision == 0)) {
      str_temp[0] = '\0';
      res_len = 0;
      len = 0;
    }
    if (ff->precision_point && str_temp[0] == '-') {
      s21_strcat(str_res, "-");
      len--;
      str_temp = s21_mixing(str_temp, len);
      mixing = 1;
    }
    if (ff->flag_plus && str_temp[0] != '-' && mixing == 0) {
      s21_strcat(str_res, "+");
      res_len++;
      ff->flag_space = 0;
    }
    if (ff->flag_space && str_temp[0] != '-' && mixing == 0) {
      s21_strcat(str_res, " ");
      res_len++;
    }
    while (ff->precision-- > len) {
      s21_strcat(str_res, "0");
      res_len++;
    }
    s21_strcat(str_res, str_temp);
    if (ff->flag_minus) {
      for (int i = 0; i < res_len; i++) {
        **str = str_res[i];
        (*str)++;
      }
    }
    for (; ff->width > res_len; ff->width--) {
      **str = ' ';
      (*str)++;
    }
    if (!ff->flag_minus) {
      for (int i = 0; i < res_len; i++) {
        **str = str_res[i];
        (*str)++;
      }
    }
    (*format)++;
  } else if (**format == 's') {
    char *str_tmp;
    str_tmp = va_arg(vl, char *);
    if (str_tmp == NULL) {
      str_tmp = "(null)";
    }
    int len = s21_strlen(str_tmp);
    int res_len = len;
    if (ff->precision_point) {
      if (ff->precision < res_len) {
        res_len = ff->precision;
      } else if (ff->precision > res_len) {
        ff->precision = res_len;
      }
    }
    if (ff->flag_minus) {
      for (int i = 0; i < res_len; i++) {
        **str = str_tmp[i];
        (*str)++;
      }
    }
    for (; ff->width > res_len; ff->width--) {
      **str = ' ';
      (*str)++;
    }
    if (!ff->flag_minus) {
      for (int j = 0; j < res_len; j++) {
        **str = str_tmp[j];
        (*str)++;
      }
    }
    (*format)++;
  } else if (**format == 'u') {
    char *str_temp = NULL;
    char str_res[1024] = {0};
    if (ff->length_l) {
      unsigned long long_tmp;
      long_tmp = va_arg(vl, unsigned long);
      str_temp = s21_lu(long_tmp);
    } else if (ff->length_h) {
      int short_tmp;
      short_tmp = va_arg(vl, int);
      str_temp = s21_hu(short_tmp);
    } else {
      long long tmp;
      tmp = va_arg(vl, long long);
      str_temp = s21_u(tmp);
    }

    int len = s21_strlen(str_temp);
    int res_len = len;
    if ((ff->precision_point) && (str_temp[0] == 48) && (ff->precision == 0)) {
      str_temp[0] = '\0';
      res_len = 0;
      len = 0;
    }
    while (ff->precision-- > len) {
      s21_strcat(str_res, "0");
      res_len++;
    }
    s21_strcat(str_res, str_temp);
    if (ff->flag_minus) {
      for (int i = 0; i < res_len; i++) {
        **str = str_res[i];
        (*str)++;
      }
    }
    for (; ff->width > res_len; ff->width--) {
      **str = ' ';
      (*str)++;
    }
    if (!ff->flag_minus) {
      for (int i = 0; i < res_len; i++) {
        **str = str_res[i];
        (*str)++;
      }
    }
    (*format)++;
  } else if (**format == 'f') {
    char *str_temp = NULL;
    char str_res[1024] = {0};
    int mixing = 0;
    if (ff->precision_point == 0) {
      ff->precision_point = 1;
      ff->precision = 6;
    }
    int n = ff->precision;
    if (ff->length_l) {
      double ldf;
      ldf = va_arg(vl, double);
      str_temp = s21_float(ldf, n);
    } else {
      double df;
      df = va_arg(vl, double);
      str_temp = s21_float(df, n);
    }
    int len = s21_strlen(str_temp);
    int res_len = len;
    if (ff->precision_point && str_temp[0] == '-') {
      s21_strcat(str_res, "-");
      len--;
      str_temp = s21_mixing(str_temp, len);
      mixing = 1;
    }
    if (ff->flag_plus && str_temp[0] != '-' && mixing == 0) {
      s21_strcat(str_res, "+");
      res_len++;
      ff->flag_space = 0;
    }
    if (ff->flag_space && str_temp[0] != '-' && mixing == 0) {
      s21_strcat(str_res, " ");
      res_len++;
    }
    while (ff->precision-- > len) {
      s21_strcat(str_res, "0");
      res_len++;
    }
    s21_strcat(str_res, str_temp);
    if (ff->flag_minus) {
      for (int i = 0; i < res_len; i++) {
        **str = str_res[i];
        (*str)++;
      }
    }
    for (; ff->width > res_len; ff->width--) {
      **str = ' ';
      (*str)++;
    }
    if (!ff->flag_minus) {
      for (int i = 0; i < res_len; i++) {
        **str = str_res[i];
        (*str)++;
      }
    }
    (*format)++;
  }
}

int parsing(const char **format, struct format_sprintf *flag) {
  int pars = 0;
  while (**format) {
    if (**format == '-' || **format == '+' || **format == ' ') {
      if (**format == '-') {
        flag->flag_minus = 1;
      } else if (**format == '+') {
        flag->flag_plus = 1;
      } else if (**format == ' ') {
        flag->flag_space = 1;
      }
      (*format)++;
    } else if (number(**format)) {
      while (number(**format)) {
        flag->width = **format - '0' + flag->width * 10;
        (*format)++;
      }
    } else if (**format == '.') {
      flag->precision_point = 1;
      (*format)++;
      while (number(**format)) {
        flag->precision = **format - '0' + flag->precision * 10;
        (*format)++;
      }
    } else if (**format == 'h' || **format == 'l') {
      if (**format == 'h') {
        flag->length_h = 1;
      } else if (**format == 'l') {
        flag->length_l = 1;
      }
      (*format)++;
    } else if (specifier(**format)) {
      pars = 1;
      break;
    } else {
      pars = 0;
      break;
    }
  }
  return pars;
}

int number(char ch) {
  int a = 0;
  if (ch >= '0' && ch <= '0' + 9) {
    a = 1;
  }
  return a;
}

int specifier(char ch) {
  int a = 0;
  if (ch == 'd' || ch == 'i' || ch == 'c' || ch == 'f' || ch == 's' ||
      ch == 'u' || ch == '%') {
    a = 1;
  }
  return a;
}

void Zero(struct format_sprintf *f) {
  f->flag_minus = 0;
  f->flag_plus = 0;
  f->flag_space = 0;
  f->length_h = 0;
  f->length_l = 0;
  f->precision = 0;
  f->width = 0;
  f->precision_point = 0;
}

char *s21_itoa(long long num) {
  static char res[1024];
  s21_clear(res);
  int i = 0;
  long n = num;
  if (n == 0) {
    res[i] = '0';
  }
  if (n == LONG_MIN) {
    n /= 10;
    res[i++] = 8 + '0';
  }
  while (n != 0) {
    if (n < 0) {
      res[i] = (n * (-1) % 10) + '0';
    } else {
      res[i] = (n % 10) + '0';
    }
    n /= 10;
    i++;
  }
  if (num < 0) {
    res[i] = '-';
  }
  s21_reverse_array(res, (int)s21_strlen(res));
  return res;
}

void s21_reverse_array(char *a, int n) {
  int l = n % 2 == 0 ? n / 2 : n / 2 + 1;
  for (int i = 0; i < l; i++) {
    char tmp = a[i];
    int j = i + 1;
    a[i] = a[n - j];
    a[n - j] = tmp;
  }
}

void s21_clear(char *str) {
  while (*str) *str++ = 0;
}

char *s21_float(long double num, int n) {
  int ro = 1;
  if (n >= 19) {
    ro = 0;
  }
  static char str[1024];
  static char str_res[1024];
  s21_clear(str);
  s21_clear(str_res);
  int minus = 0;
  int round1 = 0;
  if (num == 0) {
    int tmp_acc = n;
    str[0] = '0';
    str[1] = '.';
    int i = 2;
    while (tmp_acc--) {
      str[i++] = '0';
    }
  }
  if (signbit(num)) {
    num = (-1) * num;
    minus = 1;
  }
  long double tmp_flt;
  tmp_flt = num;
  long long tmp_int = (long long)tmp_flt;
  int tmp_acc = n;
  int j = 0;
  long double reminder = num - tmp_int;
  reminder = reminder * 10;
  if (n >= 19) {
    reminder = reminder / 10;
    n = n - 1;
  }
  while (tmp_acc > 0) {
    reminder *= 10;
    tmp_acc--;
  }
  long long k = reminder;
  if (n == 0) {
    double a = 1;
    reminder = reminder / 10;
    a = a - reminder;
    if (!(tmp_int % 2) && round(a) == 1) {
      k = 4;
    }
  }
  while ((n + 1) > 0) {
    str[j] = (k % 10) + '0';
    k /= 10;
    n--;
    j++;
  }
  str[j] = '.';
  if (tmp_int == 0) {
    str[j + 1] = '0';
  }
  while (tmp_int != 0) {
    str[(j + 1)] = (tmp_int % 10) + '0';
    j++;
    tmp_int /= 10;
  }
  int y = (int)s21_strlen(str);
  s21_reverse_array(str, y);
  if (ro) {
    if (str[(y - 1)] >= '5' && str[(y - 1)] <= '9') {
      int h = y - 2;
      while (h != -1) {
        if (str[h] == '9') {
          str[h] = '0';
          h--;
          if (h == -1) {
            round1 = 1;
          }
        } else {
          if (str[h] == '.') {
            h = h - 1;
          }
          if (str[h] != '9') {
            str[h] = str[h] + 1;
            h = -1;
          }
        }
      }
    }
  }
  if (minus) {
    s21_strcat(str_res, "-");
  }
  if (round1) {
    s21_strcat(str_res, "1");
  }
  s21_strcat(str_res, str);

  int f = (int)s21_strlen(str_res);
  if (ro) {
    str_res[f - 1] = '\0';
  }
  if (str_res[f - 2] == '.') {
    str_res[f - 2] = '\0';
  }
  return str_res;
}

char *s21_u(long long num) {
  static char resu[1024];
  s21_clear(resu);
  int i = 0;
  long long n = num;
  while (n < 0) {
    n = 4294967296 + n;
  }
  if (n == 0) {
    resu[i] = '0';
  }
  while (n != 0) {
    resu[i] = (n % 10) + '0';
    n /= 10;
    i++;
  }
  s21_reverse_array(resu, (int)s21_strlen(resu));
  return resu;
}

char *s21_hu(int num) {
  static char reshu[1024];
  s21_clear(reshu);
  int i = 0;
  int n = num;
  while (n < 0) {
    n = 65536 + n;
  }
  while (n > 65535) {
    n = n - 65536;
  }
  if (n == 0) {
    reshu[i] = '0';
  }
  while (n != 0) {
    reshu[i] = (n % 10) + '0';
    n /= 10;
    i++;
  }
  s21_reverse_array(reshu, (int)s21_strlen(reshu));
  return reshu;
}

char *s21_lu(unsigned long num) {
  static char reslu[1024];
  s21_clear(reslu);
  int i = 0;
  unsigned long n = num;
  if (n == 0) {
    reslu[i] = '0';
  }
  while (n != 0) {
    reslu[i] = (n % 10) + '0';
    n /= 10;
    i++;
  }
  s21_reverse_array(reslu, (int)s21_strlen(reslu));
  return reslu;
}

char *s21_mixing(char *str, int len) {
  for (int i = 0; i < len; i++) {
    str[i] = str[i + 1];
  }
  return str;
}
