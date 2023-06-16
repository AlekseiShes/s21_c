#include "s21_sscanf.h"


long int make_int_width(char **str) {
  long int res = 0;
  while (*(*str) <= '9' && *(*str) >= '0') {
    res *= 10;
    res += *(*str) - '0';
    ++(*str);
  }
  return res;
}

long int make_int(char **str, pars *flag, vars *var) {
  long int res = 0;
  int sign = 0;
  if (*(*str) == '-') {
    ++(*str);
    var->n++;
    sign = -1;
  } else {
    sign = 1;
  }
  if (*(*str) == '\0') {
    flag->success = -1;
  }
  while (*(*str) <= '9' && *(*str) >= '0' && flag->width--) {
    if (!flag->success && !flag->snowflake) {
      flag->success = 1;
    }
    res *= 10;
    res += *(*str) - '0';
    ++(*str);
    var->n++;
  }
  return res * sign;
}

long long int make_int_8(char **str, pars *flag,
                         vars *var) {
  long long int res = 0;
  int sign = 0;
  if (*(*str) == '-') {
    ++(*str);
    var->n++;
    sign = -1;
  } else {
    sign = 1;
  }
  if (*(*str) == '\0') {
    flag->success = -1;
  }
  while (*(*str) <= '7' && *(*str) >= '0' && flag->width--) {
    if (!flag->success && !flag->snowflake) {
      flag->success = 1;
    }
    res *= 8;
    res += *(*str) - '0';
    ++(*str);
    var->n++;
  }
  return res * sign;
}

long long int make_int_16(char **str, pars *flag,
                          vars *var) {
  long long int res = 0;
  int tmp = 0;
  int sign = 0;
  if (*(*str) == '-') {
    ++(*str);
    var->n++;
    sign = -1;
  } else {
    sign = 1;
  }
  if (*(*str) == '\0') {
    flag->success = -1;
  } else {
    if (*(*str) == '0') {
      ++(*str);
      var->n++;
      if (!flag->success && !flag->snowflake) {
        flag->success = 1;
      }
      if (*(*str) == 'x' || *(*str) == 'X') {
        ++(*str);
        var->n++;
      }
    }
  }
  while (flag->width--) {
    if ((*(*str) <= '9' && *(*str) >= '0')) {
      tmp = *(*str) - '0';
    } else if ((*(*str) <= 'F' && *(*str) >= 'A')) {
      tmp = *(*str) - 'A' + 10;
    } else if ((*(*str) <= 'f' && *(*str) >= 'a')) {
      tmp = *(*str) - 'a' + 10;
    } else {
      break;
    }
    res *= 16;
    res += tmp;
    ++(*str);
    var->n++;
    if (!flag->success && !flag->snowflake) {
      flag->success = 1;
    }
  }
  return res * sign;
}
