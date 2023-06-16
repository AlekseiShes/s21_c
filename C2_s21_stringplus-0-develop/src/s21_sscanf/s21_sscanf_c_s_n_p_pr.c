#include "s21_sscanf.h"

int s_specifier(char *res, char **str, pars *par, vars *var);
int w_s_specifier(wchar_t *res, char **str, pars *par,  vars *var);

int scan_c_func(va_list *factor, char **str, pars *par, vars* var){ 
  int res = 0;
  if ((*par).snowflake) {
    var->c = **str++;
  } else {
    if ((*par).length == 'l') *va_arg(*factor, wchar_t *) = **str++;
    else *va_arg(*factor, char *) = **str++;
    res++;
  }
  var->n++;
 return res;
}

int scan_s_func(va_list *factor, char **str, pars *par, vars* var){ 
  int res = 0;
  if (par->snowflake) {
    res += s_specifier(&(var->c), str, par, var);
  } else {
    if (par->length == 'l') 
      res += w_s_specifier(va_arg(*factor, wchar_t *), str, par, var);
    else
      res += s_specifier(va_arg(*factor, char *), str, par, var);
  }
return res;
}

int scan_n_func(va_list *factor, char **str, pars *par, vars* var){ 
    *va_arg(*factor, int *) = var->n;    
    return 0;
}

int scan_p_func(va_list *factor, char **str, pars *par, vars* var){ return 0; }
int scan_prfunc(va_list *factor, char **str, pars *par, vars* var){ return 0; }

int s_specifier(char *res, char **str, pars *par, vars *var) {
  if (**str == '\0') par->success = -1;
  while ((**str != ' ') && (**str != '\0') &&
         (**str != '\n') && (**str != '\t') && par->width) {
    if (!par->success && !par->snowflake) par->success = 1;
    *res = **str;
    ++res;
    ++(*str);
    var->n++;
    --par->width;
  }
  if (res) *res = '\0';
  return 0;
}

int w_s_specifier(wchar_t *res, char **str, pars *par,  vars *var) {
  while (res && str && *str && (**str != ' ') && (**str != '\0') &&
         (**str != '\n') && (**str != '\t') && par && par->width) {
    if (!par->success && !par->snowflake) par->success = 1;
    *res = **str;
    ++res;
    ++(*str);
    var->n++;
    --par->width;
  }
  if (res) *res = '\0';
  return 0;
}
