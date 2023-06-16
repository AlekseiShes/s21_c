#include "s21_sscanf.h"

int scan_o_func(va_list *factor, char **str, pars *par, vars* var){int res = 0; 
              if (par->snowflake) {
                res += o_specifier(&(var->u), str, par, var);
              } else {
                if (par->length == 'h') {
                  res +=
                      ho_specifier(va_arg(*factor, unsigned short int *),
                                   str, par, var);
                } else if (par->length == 'l') {
                  res +=
                      lo_specifier(va_arg(*factor, unsigned long int *),
                                   str, par, var);
                } else {
                  res += o_specifier(va_arg(*factor, unsigned int *),
                                         str, par, var);
                }
              }

return res;}
int scan_x_func(va_list *factor, char **str, pars *par, vars* var){
  int res = 0;
              if (par->snowflake) {
                res += x_specifier(&(var->u), str, par, var);
              } else {
                if (par->length == 'h') {
                  res +=
                      hx_specifier(va_arg(*factor, unsigned short int *),
                                   str, par, var);
                } else if (par->length == 'l') {
                  res +=
                      lx_specifier(va_arg(*factor, unsigned long int *),
                                   str, par, var);
                } else {
                  res += x_specifier(va_arg(*factor, unsigned int *),
                                         str, par, var);
                }
              }
  return res;
}

int o_specifier(unsigned int *num, char **str_ptr, pars *flag,
                vars *var) {
  *num = (unsigned int)make_int_8(str_ptr, flag, var);
  return 0;
}

int ho_specifier(unsigned short int *num, char **str_ptr, pars *flag,
                 vars *var) {
  *num = (unsigned short int)make_int_8(str_ptr, flag, var);
  return 0;
}

int lo_specifier(unsigned long int *num, char **str_ptr, pars *flag,
                 vars *var) {
  *num = (unsigned long int)make_int_8(str_ptr, flag, var);
  return 0;
}


int x_specifier(unsigned int *num, char **str_ptr, pars *flag,
                vars *var) {
  if (*(*str_ptr) == '0') {
    ++(*str_ptr);
    flag->success = 1;
    if ((*(*str_ptr) == 'X') || (*(*str_ptr) == 'x')) {
      --(*str_ptr);
      *num = (unsigned int)make_int_16(str_ptr, flag, var);
    }
  } else {
    *num = (unsigned int)make_int_16(str_ptr, flag, var);
  }
  return 0;
}

int hx_specifier(unsigned short int *num, char **str_ptr, pars *flag,
                 vars *var) {
  if (*(*str_ptr) == '0') {
    ++(*str_ptr);
    var->n++;
    flag->success = 1;
    if ((*(*str_ptr) == 'X') || (*(*str_ptr) == 'x')) {
      ++(*str_ptr);
      var->n++;
      *num = (unsigned short int)make_int_16(str_ptr, flag, var);
    }
  } else {
    *num = (unsigned short int)make_int_16(str_ptr, flag, var);
  }
  return 0;
}

int lx_specifier(unsigned long int *num, char **str_ptr, pars *flag,
                 vars *var) {
  if (*(*str_ptr) == '0') {
    ++(*str_ptr);
    var->n++;
    flag->success = 1;
    if ((*(*str_ptr) == 'X') || (*(*str_ptr) == 'x')) {
      ++(*str_ptr);
      var->n++;
      *num = (unsigned long int)make_int_16(str_ptr, flag, var);
    }
  } else {
    *num = (unsigned long int)make_int_16(str_ptr, flag, var);
  }
  return 0;
}
