#include "../s21_string.h"
#include "s21_sscanf.h"

void omit_space(char **str, vars *var);
int get_params(pars *flag, char **format, collection *collect, int cnt);

int s21_sscanf(const char *str, const char *format, ...) {
  int status = (str && *str == '\0') ? Err: OK;
  int cnt_suc_var = (status == OK)? 0: -1;
  char *format_ptr = (char *)format;
  char *str_ptr = (char *)str;
  va_list params_list;
  va_start(params_list, format);
  vars var = {0};
  collection collect[] = {
   {'d', scan_d_func}, {'i', scan_i_func}, {'u', scan_u_func}
  ,{'o', scan_o_func}
  ,{'x', scan_x_func}, {'X', scan_x_func}
  ,{'s', scan_s_func}, {'c', scan_c_func}
  ,{'e', scan_f_func}, {'E', scan_f_func}
  ,{'g', scan_f_func}, {'G', scan_f_func}, {'f', scan_f_func}
  ,{'n', scan_n_func} ,{'%', scan_prfunc} ,{'p', scan_p_func}  
  };
    while (*format_ptr && (status == OK)) {
      pars flag = {0};
      if (*format_ptr == '%') {
        format_ptr++;
        if ((status = get_params(&flag, &format_ptr,
         collect, sizeof(collect) / sizeof(collect[0]))) == OK) {
          s21_size_t i = 0;
          for (i = 0; i < sizeof(collect) / sizeof(collect[0]); i++){
            if (flag.specifier == collect[i].specifier){
              if (flag.specifier != 'c' && flag.specifier != 'n') {
                omit_space(&str_ptr, &var);
              } 
              cnt_suc_var += collect[i].operation(&params_list, &str_ptr, &flag, &var);
              if (flag.specifier == 'c' && *format_ptr == ' ') {
                omit_space(&str_ptr, &var);
              } 
            }
          }
          cnt_suc_var += flag.success;
        }
      } else {
        ++format_ptr;
      }
    }
  va_end(params_list);
  return cnt_suc_var;
}

int my_va_arg(va_list *va, TYPES type, void *value){
  int status = OK;
  switch (type){
    case tCHAR: *va_arg(*va, char *) = *((char *) value); break;
    case tWCHR: *va_arg(*va, wchar_t *) = *((wchar_t *) value); break;
    case tSHRT: *va_arg(*va, short int *) = *((short int *) value); break;
    case t_INT: *va_arg(*va, int *) = *(( int *) value); break;
    case tUINT: *va_arg(*va, unsigned int *) = *((unsigned int *) value); break;
    case tLINT: *va_arg(*va, long int *) = *((long int *) value); break;
    case t_FLT: *va_arg(*va, float *) = *((float *) value); break;
    case t_DBL: *va_arg(*va, double *) = *((double *) value); break;
    case tLDBL: *va_arg(*va, long double *) = *((long double *) value); break;
    /* case tVOID: *va_arg(*va, void *) = *value; break; */
    default: status = Err;
  }
  return status;
}

void omit_space(char **str, vars *var) {
  if (str && *str && var)
  while ((**str == ' ') || (**str == '\n') || (**str == '\t')) {
    ++(*str);
    var->n++;
  }
}

int get_width_from_format(pars *flag, char **format) {
  int error = 0;
  if (*(*format) == '-') {
    ++(*format);
    error = 1;
  }
  if (*(*format) == '*') {
    flag->snowflake = 1;
    ++(*format);
  } else if (*(*format) >= '0' && *(*format) <= '9') {
    flag->width = make_int_width(format);
  } else {
    flag->width = 2147483647;
  }
  if (flag->width == 0) {
    flag->width = 2147483647;
  }
  return error;
}

int get_length_from_format(pars *flag, char **format) {
  int error = 0;
  switch (*(*format)) {
    case 'h':
    case 'l':
    case 'L':
      flag->length = *(*format);
      ++(*format);
      break;
    default:
      flag->length = -1;
      break;
  }
  return error;
}

int get_specifier_from_format(pars *flag, char **format, collection *collect, int cnt) {
  int error = 1;
  for(int i = 0 ; i < cnt; i++)
    if(**format == collect[i].specifier){
      flag->specifier = *(*format);
      ++(*format);
      error = 0;      
    }
  return error;
}

int get_params(pars *flag, char **format, collection *collect, int cnt) {
  return(!get_width_from_format(flag, format)&&
       !get_length_from_format(flag, format)&&
       !get_specifier_from_format(flag, format, collect, cnt))? 0: 1;
}
