#include "s21_sscanf.h"

int scan_f_func(va_list *factor, char **str, pars *par, vars* var){
    int res = 0;
              if (par->length == 'l') {
                if (par->snowflake) {
                  res += lf_specifier(&(var->d), str, par, var);
                } else {
                  res += lf_specifier(va_arg(*factor, double *),
                                          str, par, var);
                }
              } else if (par->length == 'L') {
                if (par->snowflake) {
                  res += Lf_specifier(&(var->ld), str, par, var);
                } else {
                  res += Lf_specifier(va_arg(*factor, long double *),
                                          str, par, var);
                }
              } else {
                if (par->snowflake) {
                  res += f_specifier(&(var->f), str, par, var);
                } else {
                  res += f_specifier(va_arg(*factor, float *), str,
                                         par, var);
                }
              }

    return res;
}


int f_specifier(float *num, char **str_ptr, pars *flag,
                vars *var) {
  *num = (float)make_long_double(str_ptr, flag, var);
  return 0;
}

int lf_specifier(double *num, char **str_ptr, pars *flag,
                 vars *var) {
  *num = (double)make_long_double(str_ptr, flag, var);
  return 0;
}

int Lf_specifier(long double *num, char **str_ptr, pars *flag,
                 vars *var) {
  *num = make_long_double(str_ptr, flag, var);
  return 0;
}

long double make_long_double(char **str, pars *flag,
                             vars *var) {
  long double res = 0;
  int cnt = 0;
  long int power = 0;
  int sign = 0;
  if (*(*str) == '\0') {
    flag->success = -1;
  }
  if (*(*str) == '-') {
    sign = -1;
    ++(*str);
  } else {
    sign = 1;
  }
  while ((*(*str) <= '9' && *(*str) >= '0') && flag->width--) {
    if (!flag->success) {
      if (!flag->snowflake) {
        flag->success = 1;
      }
    }
    res *= 10;
    res += *(*str) - '0';
    ++(*str);
    var->n++;
  }
  if (*(*str) == '.' && flag->width--) {
    ++(*str);
    var->n++;
    while ((*(*str) <= '9' && *(*str) >= '0') && flag->width--) {
      res *= 10;
      res += *(*str) - '0';
      ++cnt;
      ++(*str);
      var->n++;
    }
  }
  while (cnt--) {
    res /= 10;
  }

  if ((*(*str) == 'e' || *(*str) == 'E') && flag->width--) {
    ++(*str);
    var->n++;
    power = make_int(str, flag, var);
    if (power >= 0) {
      while (power > 0 && res != 1.0 / 0.0) {
        --power;
        res *= 10;
      }
    } else {
      while (power < 0 && res != 1.0 / 0.0) {
        res /= 10;
        power++;
      }
    }
  }
  return res * sign;
}
