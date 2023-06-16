#ifndef SRC_S21_SSCANF_H_
#define SRC_S21_SSCANF_H_
#include <float.h>
#include <math.h>
#include <wchar.h>

#include "../s21_string.h"

/*parametrs*/
typedef struct pars {
  int width;
  int snowflake;
  char length;
  char specifier;
  int success;
} pars;

typedef struct vars {
  int i;
  unsigned int u;
  char c;
  double d;
  long double ld;
  float f;
  void *p;
  int n;
}vars;

typedef enum {
    tCHAR
  , tWCHR  
  , tSHRT
  , t_INT
  , tUINT
  , tLINT
  , t_FLT
  , t_DBL
  , tLDBL
  , tVOID
} TYPES;

typedef struct collection {
  char specifier;
  int (*operation)(va_list *factor, char **str, pars *par, vars* var);
} collection;

int scan_i_func(va_list *factor, char **str, pars *par, vars* var);
int scan_o_func(va_list *factor, char **str, pars *par, vars* var);
int scan_x_func(va_list *factor, char **str, pars *par, vars* var);
int scan_d_func(va_list *factor, char **str, pars *par, vars* var);
int scan_u_func(va_list *factor, char **str, pars *par, vars* var);
int scan_s_func(va_list *factor, char **str, pars *par, vars* var);
int scan_f_func(va_list *factor, char **str, pars *par, vars* var);
int scan_c_func(va_list *factor, char **str, pars *par, vars* var);
int scan_n_func(va_list *factor, char **str, pars *par, vars* var);
int scan_p_func(va_list *factor, char **str, pars *par, vars* var);
int scan_prfunc(va_list *factor, char **str, pars *par, vars* var);

int my_va_arg(va_list *va, TYPES type, void *value);

int i_specifier(int *num, char **str_ptr, pars *flag, vars *var);
int hi_specifier(short int *num, char **str_ptr, pars *flag,
                 vars *var);
int li_specifier(long int *num, char **str_ptr, pars *flag,
                 vars *var);
int o_specifier(unsigned int *num, char **str_ptr, pars *flag,
                vars *var);
int ho_specifier(unsigned short int *num, char **str_ptr, pars *flag,
                 vars *var);
int lo_specifier(unsigned long int *num, char **str_ptr, pars *flag,
                 vars *var);
int x_specifier(unsigned int *num, char **str_ptr, pars *flag,
                vars *var);
int hx_specifier(unsigned short int *num, char **str_ptr, pars *flag,
                 vars *var);
int lx_specifier(unsigned long int *num, char **str_ptr, pars *flag,
                 vars *var);
long int make_int_width(char **str);
long int make_int(char **str, pars *flag, vars *var);
long long int make_int_8(char **str, pars *flag,
                         vars *var);
long long int make_int_16(char **str, pars *flag,
                          vars *var);
int d_specifier(/*int *num*/
va_list *factor, char **str_ptr, pars *flag,
                vars *var);
int d_specifier_(int *num, char **str_ptr, pars *flag,
                vars *var);                
int hd_specifier(short int *num, char **str_ptr, pars *flag,
                 vars *var);
int ld_specifier(long int *num, char **str_ptr, pars *flag,
                 vars *var);
int u_specifier(unsigned int *num, char **str_ptr, pars *flag,
                vars *var);
int hu_specifier(unsigned short int *num, char **str_ptr, pars *flag,
                 vars *var);
int lu_specifier(unsigned long int *num, char **str_ptr, pars *flag,
                 vars *var);
long double make_long_double(char **str, pars *flag,
                             vars *var);
int f_specifier(float *num, char **str_ptr, pars *flag,
                vars *var);
int lf_specifier(double *num, char **str_ptr, pars *flag,
                 vars *var);
int Lf_specifier(long double *num, char **str_ptr, pars *flag,
                 vars *var);

#endif  // SRC_S21_SSCANF_H_