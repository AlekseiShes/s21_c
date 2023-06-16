#include "s21_sscanf.h"

int scan_d_func(va_list *factor, char **str, pars *par, vars* var){ 
  int res = 0;  
  if (par->snowflake) {
    var->i = (int)make_int(str, par, var);
    res += d_specifier_(&(var->i), str, par, var);
  } else {
    if (par->length == 'h') {
      //void* p = *(short int *);
      //*va_arg(*factor, short int *) = (short int)make_int(str, par, var);
      //*va_arg(*factor, short int *) = (short int)make_int(str, par, var);
      short int temp_s = (short int)make_int(str, par, var);
      my_va_arg(factor, tSHRT, &temp_s);

    } else if (par->length == 'l') {
      //*va_arg(*factor, long int *) = make_int(str, par, var);
      long temp_l = make_int(str, par, var);
      my_va_arg(factor, tLINT, &temp_l);
    } else {
      // *va_arg(*factor, int *) = (int)make_int(str, par, var);
      int temp = make_int(str, par, var);
      my_va_arg(factor, t_INT, &temp);
    }
  }
  return res;
}
int scan_u_func(va_list *factor, char **str, pars *par, vars* var){
    int res = 0;
  if (par->snowflake) {
    res += u_specifier(&(var->u), str, par, var);
  } else {
    if (par->length == 'h') {
      res +=
          hu_specifier(va_arg(*factor, unsigned short int *),
           str, par, var);
    } else if (par->length == 'l') {
      res +=
          lu_specifier(va_arg(*factor, unsigned long int *),
           str, par, var);
    } else {
      res += u_specifier(va_arg(*factor, unsigned int *),
     str, par, var);
    }
  }
  return res;
}
int scan_i_func(va_list *factor, char **str, pars *par, vars* var){
    int res = 0; 
  if (par->snowflake) {
    res += i_specifier(&(var->i), str, par, var);
  } else {
    if (par->length == 'h') {
      res += hi_specifier(va_arg(*factor, short int *),
      str, par, var);
    } else if (par->length == 'l') {
      res += li_specifier(va_arg(*factor, long int *),
      str, par, var);
    } else {
      res += i_specifier(va_arg(*factor, int *), str,
     par, var);
    }
  }

    return res;
}

int i_specifier(int *num, char **str_ptr, pars *flag,
    vars *var) {
  if (*(*str_ptr) == '0') {
    ++(*str_ptr);
    var->n++;
    if ((*(*str_ptr) == 'X') || (*(*str_ptr) == 'x')) {
      ++(*str_ptr);
      var->n++;
      *num = (int)make_int_16(str_ptr, flag, var);
    } else {
      *num = (int)make_int_8(str_ptr, flag, var);
    }
  } else {
    *num = (int)make_int(str_ptr, flag, var);
  }
  return 0;
}

int hi_specifier(short int *num, char **str_ptr, pars *flag,
     vars *var) {
  if (*(*str_ptr) == '0') {
    ++(*str_ptr);
    var->n++;
    if ((*(*str_ptr) == 'X') || (*(*str_ptr) == 'x')) {
      ++(*str_ptr);
      var->n++;
      *num = (short int)make_int_16(str_ptr, flag, var);
    } else {
      *num = (short int)make_int_8(str_ptr, flag, var);
    }
  } else {
    *num = (short int)make_int(str_ptr, flag, var);
  }
  return 0;
}

int li_specifier(long int *num, char **str_ptr, pars *flag,
     vars *var) {
  if (*(*str_ptr) == '0') {
    ++(*str_ptr);
    var->n++;
    if ((*(*str_ptr) == 'X') || (*(*str_ptr) == 'x')) {
      ++(*str_ptr);
      var->n++;
      *num = (long int)make_int_16(str_ptr, flag, var);
    } else {
      *num = (long int)make_int_8(str_ptr, flag, var);
    }
  } else {
    *num = (long int)make_int(str_ptr, flag, var);
  }
  return 0;
}


int d_specifier_(int *num, char **str_ptr, pars *flag,
    vars *var) {
  *num = (int)make_int(str_ptr, flag, var);
  return 0;
}

int d_specifier(/*int *num*/ va_list *factor, char **str_ptr, pars *flag,
    vars *var) {
  *va_arg(*factor, int*) = (int)make_int(str_ptr, flag, var);
  return 0;
}
/*
int hd_specifier(short int *num, char **str_ptr, pars *flag,
     vars *var) {
  *num = (short int)make_int(str_ptr, flag, var);
  return 0;
}

int ld_specifier(long int *num, char **str_ptr, pars *flag,
     vars *var) {
  *num = make_int(str_ptr, flag, var);
  return 0;
}*/

int u_specifier(unsigned int *num, char **str_ptr, pars *flag,
    vars *var) {
  *num = (unsigned int)make_int(str_ptr, flag, var);
  return 0;
}

int hu_specifier(unsigned short int *num, char **str_ptr, pars *flag,
     vars *var) {
  *num = (unsigned short int)make_int(str_ptr, flag, var);
  return 0;
}

int lu_specifier(unsigned long int *num, char **str_ptr, pars *flag,
     vars *var) {
  *num = (unsigned long int)make_int(str_ptr, flag, var);
  return 0;
}
