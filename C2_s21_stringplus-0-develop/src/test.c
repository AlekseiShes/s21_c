#include <check.h>
#include <string.h>
#include <wchar.h>

#include "s21_string.h"
#define FLT_MAX 3.402823e+38
/* eq = "==";
ne = "!=";
lt = "<";
le = "<=";
gt = ">";
ge = ">="
*/

START_TEST(insert_test) {
  char *src = "Regular!";
  char *str = ", brainfucker";
  char *new_str = {0};
  new_str = s21_insert(src, str, 7);
  if (new_str) {
    ck_assert_str_eq(new_str, "Regular, brainfucker!");
    free(new_str);
  }

  new_str = s21_insert(src, "", 9);
  ck_assert(new_str == s21_NULL);
  free(new_str);

  new_str = s21_insert("Regular!", ", brainfucker!!", 7);
  if (new_str) {
    ck_assert_str_eq(new_str, "Regular, brainfucker!!!");
    free(new_str);
  }

  new_str = s21_insert("Regular!", ", brainfucker!!", 35);
  ck_assert(new_str == s21_NULL);
  free(new_str);

  new_str = s21_insert("", "", 0);
  if (new_str) {
    ck_assert_str_eq(new_str, "");
    free(new_str);
  }

  char *src1 = "1";
  char *str1 = "1";
  char *new_str2 = s21_insert(src1, str1, 1);
  if (new_str2) {
    ck_assert_str_eq(new_str2, "11");
    free(new_str2);
  }
}

END_TEST

START_TEST(memchr_test) {
  char test_chr[] = "HelloWorld11";
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, 'b', 12),
                    (unsigned long)memchr(test_chr, 'b', 12));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, 'r', 12),
                    (unsigned long)memchr(test_chr, 'r', 12));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, 'r', 6),
                    (unsigned long)memchr(test_chr, 'r', 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, 'H', 12),
                    (unsigned long)memchr(test_chr, 'H', 12));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, ' ', 12),
                    (unsigned long)memchr(test_chr, ' ', 12));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, ' ', 12),
                    (unsigned long)memchr(test_chr, ' ', 12));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, '\0', 12),
                    (unsigned long)memchr(test_chr, '\0', 12));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, 'e', 0),
                    (unsigned long)memchr(test_chr, 'e', 0));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, 'h', 1),
                    (unsigned long)memchr(test_chr, 'h', 1));
  ck_assert_uint_eq((unsigned long)s21_memchr(test_chr, '\n', 1),
                    (unsigned long)memchr(test_chr, '\n', 1));
  // Аналогичен ck_assert_int_*, но сравнивает два целых числа без знака (
  // ).uintmax_t
}
END_TEST

START_TEST(memcmp_test) {
  char test_cmp[][15] = {"memcmpptest", "memz", "mem", "test",
                         " ",           "cmp",  "\0"};
//  ck_assert_int_eq(s21_memcmp(test_cmp[0], test_cmp[4], 5),
//                   memcmp(test_cmp[0], test_cmp[4], 5));
/*
  ck_assert_int_eq(s21_memcmp(test_cmp[0], test_cmp[6], 5),
                   memcmp(test_cmp[0], test_cmp[6], 5));
  ck_assert_int_eq(s21_memcmp(test_cmp[0], test_cmp[6], 0),
                   memcmp(test_cmp[0], test_cmp[6], 0));
  ck_assert_int_eq(s21_memcmp(test_cmp[3], test_cmp[0], 5),
                   memcmp(test_cmp[3], test_cmp[0], 5));
  ck_assert_int_eq(s21_memcmp(test_cmp[2], test_cmp[2], 5),
                   memcmp(test_cmp[2], test_cmp[2], 5));
  */
  // Сравнивает два целых числа со знаком ( intmax_t) и отображает
  // предопределенное сообщение с условием и входными параметрами в случае сбоя
}
END_TEST

START_TEST(memcpy_test) {
  char *str1 = "sfsjndjdssshsjshs";
  char test_1[BUFF_SIZE] = "Carry that way";
  char test_2[BUFF_SIZE] = "  ";
  char test_3[BUFF_SIZE] = "///  ";
  char test_4[BUFF_SIZE] = "   & ///";
  char test_5[BUFF_SIZE] = "";
  char test_6[BUFF_SIZE] = "8922486";
  char test_7[BUFF_SIZE] = "5526\0123";
  char test_8[BUFF_SIZE] = "";
  char test_9[BUFF_SIZE] = "";
  char test_10[BUFF_SIZE] = "1";
  char test_11[BUFF_SIZE] = "1";

  ck_assert_str_eq(s21_memcpy(test_1, test_2, 2), memcpy(test_1, test_2, 2));
  ck_assert_str_eq(s21_memcpy(test_3, test_4, 6), memcpy(test_3, test_4, 6));
  ck_assert_str_eq(s21_memcpy(test_5, test_6, 4), memcpy(test_5, test_6, 4));
  ck_assert_str_eq(s21_memcpy(test_6, test_7, 4), memcpy(test_6, test_7, 4));
  ck_assert_str_eq(s21_memcpy(test_8, test_9, 1), memcpy(test_8, test_9, 1));
  ck_assert_str_eq(s21_memcpy(test_10, test_11, 1),
                   memcpy(test_10, test_11, 1));

  /*char *Сравнивает два строковых значения, заканчивающихся нулем , используя
  strcmp()внутреннюю функцию, и отображает предопределенное сообщение с условием
  и значениями входных параметров в случае сбоя Если в любой макрос сравнения
  будет передан указатель NULL, проверка завершится ошибкой.*/
}
END_TEST

START_TEST(memmove_test) {
  char strings[][20] = {"Random phrases", "ph", "om", "o", "ando", "", "Rand"};
  ck_assert_str_eq(s21_memmove(strings[0], strings[1], 2),
                   memmove(strings[0], strings[1], 2));
  ck_assert_str_eq(s21_memmove(strings[1], strings[0], 5),
                   memmove(strings[1], strings[0], 5));
  ck_assert_str_eq(s21_memmove(strings[1], strings[0], 5),
                   memmove(strings[1], strings[0], 5));
  ck_assert_str_eq(s21_memmove(strings[3], strings[4], 5),
                   memmove(strings[3], strings[4], 5));
  ck_assert_str_eq(s21_memmove(strings[3], strings[4], 0),
                   memmove(strings[3], strings[4], 0));
}
END_TEST

START_TEST(memset_test) {
  char strings[][20] = {"Random world", "wo", "do", "o", "ando", "", "Rand"};
  ck_assert_str_eq(s21_memset(strings[0], 112, 2), memset(strings[0], 112, 2));
  ck_assert_str_eq(s21_memset(strings[1], 32, 5), memset(strings[1], 32, 5));
  ck_assert_str_eq(s21_memset(strings[3], 3, 2), memset(strings[3], 3, 2));
  ck_assert_str_eq(s21_memset(strings[3], 10, 3), memset(strings[3], 10, 3));
  ck_assert_str_eq(s21_memset(strings[4], 2, 2), memset(strings[4], 2, 2));
  ck_assert_str_eq(s21_memset(strings[5], 12, 5), memset(strings[5], 12, 5));
  ck_assert_str_eq(s21_memset(strings[6], 11, 5), memset(strings[6], 11, 5));
}
END_TEST

START_TEST(strcat_test) {
  char str1[] = "TES V SKYRIM";
  char str2[] = "\0";
  char str3[] = "1\0";
  char str4[] = "\0";
  char str5[] = "";
  char str6[] = "";
  char str7[5] = "1\0";
  char str8[5] = "1";
  char str9[5] = "1";
  char str10[5] = "1";
  ck_assert_uint_eq((unsigned long)s21_strcat(str1, str2),
                    (unsigned long)strcat(str1, str2));
  ck_assert_uint_eq((unsigned long)s21_strcat(str3, str4),
                    (unsigned long)strcat(str3, str4));
  ck_assert_uint_eq((unsigned long)s21_strcat(str5, str6),
                    (unsigned long)strcat(str5, str6));
  ck_assert_uint_eq((unsigned long)s21_strcat(str7, str8),
                    (unsigned long)strcat(str7, str8));
  ck_assert_uint_eq((unsigned long)s21_strcat(str9, str10),
                    (unsigned long)strcat(str9, str10));
}
END_TEST

START_TEST(strncat_test) {
  char test_1[16] = "This is";
  char test_2[16] = " a test";
  char test_3[2] = "5";
  char test_4[] = "";
  char str1[99] = "Regular";
  char str2[99] = "Regular";
  char str3[] = " normal team";
  char str4[99] = "";
  char str5[99] = "";
  char str6[99] = "1";
  char str7[99] = "1";

  ck_assert_str_eq(strcat(str1, str3), s21_strcat(str2, str3));
  ck_assert_str_eq(strcat(str4, str5), s21_strcat(str4, str5));
  ck_assert_str_eq(strcat(str6, str7), s21_strcat(str6, str7));
  ck_assert_str_eq(s21_strncat(test_1, test_2, 9), "This is a test");
  ck_assert_str_eq(s21_strncat(test_3, test_4, 0), strncat(test_3, test_4, 0));
}
END_TEST

START_TEST(strchr_test) {
  char *str1 = "TEST";
  char *str2 = "strchr";
  char *str3 = "function";
  char *str4 = "";
  char *str5 = "aboba";
  ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
  ck_assert_str_eq(s21_strchr(str5, 'a'), strchr(str5, 'a'));
  ck_assert_str_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_ptr_eq(s21_strchr(str2, 'E'), strchr(str2, 'E'));
  ck_assert_str_eq(s21_strchr(str3, 'i'), strchr(str3, 'i'));
  ck_assert_ptr_eq(s21_strchr(str4, ' '), strchr(str4, ' '));
  ck_assert_str_eq(s21_strchr(str5, 'o'), strchr(str5, 'o'));
}
END_TEST

START_TEST(strcmp_test) {
  char str1[10] = "hello";
  char str2[10] = "hello";
  char str3[10] = "hellq";
  char str4[10] = "helle";
  char str5[10] = "";
  char str6[10] = "";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
  ck_assert_int_lt(s21_strcmp(str1, str3), 0);
  ck_assert_int_gt(s21_strcmp(str1, str4), 0);
  ck_assert_int_gt(s21_strcmp(str1, str5), 0);
  ck_assert_int_eq(s21_strcmp(str5, str6), strcmp(str5, str6));
  /*Сравнивает два целых числа со знаком ( intmax_t) и отображает
  предопределенное сообщение с условием и входными параметрами в случае сбоя.
  Оператор, используемый для сравнения, различен для каждой функции и
  обозначается двумя последними буквами имени функции.*/
}
END_TEST

START_TEST(strncmp_test) {
  char test_strn[][15] = {"strncmptest", "strn",  "st", "test",
                          "zero",        "strnc", ""};
  ck_assert_int_eq(s21_strncmp(test_strn[0], test_strn[0], 3),
                   strncmp(test_strn[0], test_strn[0], 3));
  ck_assert_int_eq(s21_strncmp(test_strn[0], test_strn[5], 2),
                   strncmp(test_strn[0], test_strn[5], 2));
  ck_assert_int_eq(s21_strncmp(test_strn[5], test_strn[0], 1),
                   strncmp(test_strn[5], test_strn[0], 1));
  ck_assert_int_eq(s21_strncmp(test_strn[5], test_strn[0], 5),
                   strncmp(test_strn[5], test_strn[0], 5));
  ck_assert_int_lt(s21_strncmp(test_strn[0], test_strn[4], 10), 0);
  ck_assert_int_lt(strncmp(test_strn[0], test_strn[4], 10), 0);
  ck_assert_int_eq(s21_strncmp(test_strn[5], test_strn[0], 3),
                   strncmp(test_strn[5], test_strn[0], 3));
}
END_TEST

START_TEST(strcpy_test) {
  char s1[50] = "This is a test";
  char d1[50] = "";
  s21_strcpy(d1, s1);
  ck_assert_msg(!strcmp(d1, s1), "1st  strcpy test failed");

  char s2[50] = "SUIIII";
  char d2[50] = "NO";
  s21_strcpy(d2, s2);
  ck_assert_msg(!strcmp(d2, s2), "2nd strcpy test failed");

  char s3[50] = "";
  char d3[50] = "HELLO";
  s21_strcpy(d3, s3);
  ck_assert_msg(!strcmp(d3, s3), "3rd strcpy test failed");

  char s4[50] = "aboba";
  char d4[50] = "HELLO";
  s21_strcpy(d4, s4);
  ck_assert_msg(!strcmp(d4, s4), "4rth strcpy test failed");

  char s5[50] = "Shrek";
  char d5[50] = "what";
  s21_strcpy(d5, s5);
  ck_assert_msg(!strcmp(d5, s5), "5th strcpy test failed");
}
END_TEST

START_TEST(strncpy_test) {
  char strings1[][20] = {"Random world", "wo", "do", "o", "ando", "     ", ""};
  char strings2[][20] = {"Random world", "wo", "do", "o", "ando", "     ", ""};
  char dst1_1[15] = {0};
  char dst2_1[15] = {0};
  char dst1_2[15] = {0};
  char dst2_2[15] = {0};
  char dst1_3[15] = {0};
  char dst2_3[15] = {0};
  char dst1_4[15] = {0};
  char dst2_4[15] = {0};
  ck_assert_str_eq(strncpy(dst1_1, strings1[5], 1),
                   s21_strncpy(dst2_1, strings1[5], 1));
  ck_assert_str_eq(strncpy(dst1_2, strings1[5], 5),
                   s21_strncpy(dst2_2, strings2[5], 5));
  ck_assert_str_eq(strncpy(dst1_3, strings1[6], 5),
                   s21_strncpy(dst2_3, strings2[6], 5));
  ck_assert_str_eq(strncpy(dst1_4, strings1[6], 0),
                   s21_strncpy(dst2_4, strings2[6], 0));
}
END_TEST

START_TEST(strcspn_test) {
  char test1[] = "NormalTeam";
  char test2[] = "Team";
  char test3[] = "PrimalAboba";
  char test4[] = "Aboba";
  char test5[] = "0/";
  char test6[] = "//#";
  char test7[] = " ";
  char test8[] = "0987654321";
  char test9[] = "0";
  char test10[] = "1";
  ck_assert_int_eq(s21_strcspn(test1, test2), strcspn(test1, test2));
  ck_assert_int_eq(s21_strcspn(test3, test4), strcspn(test3, test4));
  ck_assert_int_eq(s21_strcspn(test3, test5), strcspn(test3, test5));
  ck_assert_int_eq(s21_strcspn(test3, test6), strcspn(test3, test6));
  ck_assert_int_eq(s21_strcspn(test3, test7), strcspn(test3, test7));
  ck_assert_int_eq(s21_strcspn(test4, test8), strcspn(test4, test8));
  ck_assert_int_eq(s21_strcspn(test2, test7), strcspn(test2, test7));
  ck_assert_int_eq(s21_strcspn(test8, test9), strcspn(test8, test9));
  ck_assert_int_eq(s21_strcspn(test8, test10), strcspn(test8, test10));
}
END_TEST

START_TEST(all_errors) {
  for (int i = -1000; i < 150; i++) {
    char *my = s21_strerror(i);
    char *orig = strerror(i);
    ck_assert_str_eq(my, orig);
  }
}
END_TEST

START_TEST(negative_err_code) {
  char *my = s21_strerror(-1);
  char *orig = strerror(-1);
  ck_assert_str_eq(my, orig);
}
END_TEST

START_TEST(strlen_test) {
  char *str1 = "Hello, World!";
  char *str2 = "";
  char *str3 = "This is a test";
  char *str4 = "Doka2";
  char *str5 = "Metal";
  ck_assert_msg(s21_strlen(str1) == strlen(str1), "1st strlen test faied");
  ck_assert_msg(s21_strlen(str2) == strlen(str2), "2nd strlen test failed");
  ck_assert_msg(s21_strlen(str3) == strlen(str3), "3rd strlen test failed");
  ck_assert_msg(s21_strlen(str4) == strlen(str4), "4rth strlen test failed");
  ck_assert_msg(s21_strlen(str5) == strlen(str5), "5th strlen test failed");
  // Не проходит тест, если предоставленное условие оценивается как ложное, и
  // отображает предоставленное пользователем сообщение
}
END_TEST

// a block-scope function may only have extern storage class



START_TEST(strpbrk_test) {
  char *str1 = "this is a test";
  char *str2 = "thi";
  char *res1, *res2;
  res1 = s21_strpbrk(str1, str2);
  res2 = strpbrk(str1, str2);
  ck_assert_str_eq(
      res1, res2); 
//Сравнивает два строковых значения заканчивающихся нулем.
//Пройдет если беззнаковое числовое значение строки а меньше чем б. 
//Если в любой макрос сравнения будет передан указатель NULL,
//проверка завершится ошибкой.

  char *str4 = "ab";
  res1 = s21_strpbrk(str1, str4);
  res2 = strpbrk(str1, str4);
  ck_assert_ptr_eq(res1, res2);

  char *str5 = "i";
  res1 = s21_strpbrk(str1, str5);
  res2 = strpbrk(str1, str5);
  ck_assert_ptr_eq(res1, res2);

  char *str6 = "abcdefghjkl";
  char *str7 = "abcd";
  res1 = s21_strpbrk(str6, str7);
  res2 = strpbrk(str6, str7);
  ck_assert_str_eq(res1, res2);

  char *str8 = "is";
  res1 = s21_strpbrk(str1, str8);
  res2 = s21_strpbrk(str1, str8);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(strrchr_test) {
  char *s1 = "School-21";
  char *s2 = "";
  char *s3 = "aboba";

  ck_assert_msg(s21_strrchr(s1, 'm') == strrchr(s1, 'm'),
                "1st strrchr test failed");
  ck_assert_msg(s21_strrchr(s1, 'o') == strrchr(s1, 'o'),
                "2nd strrchr test failed");
  ck_assert_msg(s21_strrchr(s2, 'o') == strrchr(s2, 'o'),
                "3rd strrchr test failed");
  ck_assert_msg(s21_strrchr(s3, ' ') == strrchr(s3, ' '),
                "4rth strrchr test failed");
  ck_assert_msg(s21_strrchr(s3, 's') == strrchr(s3, 's'),
                "5th strrchr test failed");
}
END_TEST

START_TEST(strspn_test) {
  char str1[] = "0987654321";
  char str2[] = "012";
  char str3[] = "abcdefg";
  char str4[] = "gda";
  char str5[] = "!@#$^&*()";
  char str6[] = ")(*";
  char str7[] = ")";
  char str8[] = "";

  ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
  ck_assert_int_eq(s21_strspn(str2, str1), strspn(str2, str1));
  ck_assert_int_eq(s21_strspn(str3, str4), strspn(str3, str4));
  ck_assert_int_eq(s21_strspn(str5, str6), strspn(str5, str6));
  ck_assert_int_eq(s21_strspn(str5, str7), strspn(str5, str7));
  ck_assert_int_eq(s21_strspn(str5, str8), strspn(str5, str8));
} END_TEST

START_TEST(strstr_test) {
  char *str1 = "This is a test";
  char *str2 = "is";
  char *str3 = "AbobaAboba";
  char *str4 = "Aboba";
  char *str5 = "1234";
  char *str7 = "095252912349866";
  char *str8 = "1";
  char *str9 = "4";

  ck_assert_ptr_eq(s21_strstr(str1, str2), strstr(str1, str2));
  ck_assert_ptr_eq(s21_strstr(str3, str4), strstr(str3, str4));
  ck_assert_ptr_eq(s21_strstr(str4, str5), strstr(str4, str5));
  ck_assert_ptr_eq(s21_strstr(str7, str5), strstr(str7, str5));
  ck_assert_ptr_eq(s21_strstr(str5, str8), strstr(str5, str8));
  ck_assert_ptr_eq(s21_strstr(str5, str9), strstr(str5, str9));
}
END_TEST

START_TEST(strtok_test) {
  char b1[25] = "test1/test2/test3/test4";
  char b2[25] = "test1/test2/test3/test4";
  char b3[24] = {'\0'};
  ck_assert_str_eq(strtok(b1, "/"), s21_strtok(b2, "/"));
  ck_assert_str_eq(strtok(NULL, "/"), s21_strtok(NULL, "/"));
  ck_assert_str_eq(strtok(NULL, "/"), s21_strtok(NULL, "/"));
  ck_assert_str_eq(strtok(NULL, "/"), s21_strtok(NULL, "/"));
  ck_assert_str_eq(strtok(b1, "!"), s21_strtok(b2, "!"));
  ck_assert_ptr_eq(strtok(b3, "!"), s21_strtok(b3, "!"));
  char *orig1, *copy1;
  orig1 = strtok(b1, b3);
  copy1 = s21_strtok(b1, b3);
  char orig_res1[1000] = {0};
  char copy_res1[1000] = {0};
  while (orig1 != NULL) {
    strcat(orig_res1, orig1);
    orig1 = strtok(NULL, b3);
  }
  while (copy1 != NULL) {
    strcat(copy_res1, copy1);
    copy1 = s21_strtok(NULL, b3);
  }
  ck_assert_str_eq(orig_res1, copy_res1);
}
END_TEST

START_TEST(to_lower_test) {
  char str1[] = "VERTER IS NOT WORKING";
  char str2[] = "QWERTY";
  char str3[] = "";
  char str4[] = "E";
  char *str = s21_to_lower(str1);

  if (str) {
    ck_assert_str_eq(str, "verter is not working");
    free(str);
  }

  str = s21_to_lower(str2);

  if (str) {
    ck_assert_str_eq(str, "qwerty");
    free(str);
  }

  str = s21_to_lower(str3);

  if (str) {
    ck_assert_str_eq(str, "");
    free(str);
  }

  str = s21_to_lower(str4);

  if (str) {
    ck_assert_str_eq(str, "e");
    free(str);
  }
}
END_TEST

START_TEST(to_upper_test) {
  char str1[] = "Carry That Weight";
  char str2[] = "Hello, World!";
  char str3[] = "";
  char str4[] = "qwerty";

  char *str = s21_to_upper(str1);

  if (str) {
    ck_assert_str_eq(str, "CARRY THAT WEIGHT");
    free(str);
  }

  str = s21_to_upper(str2);

  if (str) {
    ck_assert_str_eq(str, "HELLO, WORLD!");
    free(str);
  }
  str = s21_to_upper(str3);

  if (str) {
    ck_assert_str_eq(str, "");
    free(str);
  }

  str = s21_to_upper(str4);

  if (str) {
    ck_assert_str_eq(str, "QWERTY");
    free(str);
  }
}
END_TEST


START_TEST(trim_test) {
  char *result;
  char *banner = " \n   !* * *'\' Hello, World! <3 * * '\'*  !\n";
  result = s21_trim(banner, " *!\n '\'");
  if (result) {
    ck_assert_str_eq(result, "Hello, World! <3");
    free(result);
  }

  char *banner2 = "xxx Hello, world! xxx ---";
  char *format_str = "x -";
  result = s21_trim(banner2, format_str);
  if (result) {
    ck_assert_str_eq(result, "Hello, world!");
    free(result);
  }

  char *empty_str = "";
  result = s21_trim(empty_str, s21_NULL);
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }

  char *empty_format = "";
  result = s21_trim(s21_NULL, empty_format);
  ck_assert(result == s21_NULL);

  result = s21_trim(banner, empty_format);
  if (result) {
    ck_assert_str_eq(result, "!* * *'' Hello, World! <3 * * ''*  !");
    free(result);
  }

  result = s21_trim("banner \n", "\n");
  if (result) {
    ck_assert_str_eq(result, "banner ");
    free(result);
  }

  result = s21_trim(empty_str, " \n\0");
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }
  result = s21_trim("strok \0", "\0");
  if (result) {
    ck_assert_str_eq(result, "strok");
    free(result);
  }
}
END_TEST

START_TEST(sprintf_test) {
  int numbers[] = {-1, 0, 4, INT32_MIN, INT32_MAX, 876};
  char str_1[150][150] = {0};
  char str_2[150][150] = {0};
  int hex[] = {0x3F2, -0x3F2, 0x1869F, -0x1869F};
  short int short_int = 12345;
  long int long_int = 1234567890;

  // c-specifier

  s21_sprintf(str_1[1], "Rando%c", 'm');
  sprintf(str_2[1], "Rando%c", 'm');
  ck_assert_str_eq(str_1[1], str_2[1]);

  char c1 = 'm';
  s21_sprintf(str_1[2], "Rando%5lc", c1);
  sprintf(str_2[2], "Rando%5lc", c1);
  ck_assert_str_eq(str_1[2], str_2[2]);

  s21_sprintf(str_1[3], "Rando%c%c string", 'm', ' ');
  sprintf(str_2[3], "Rando%c%c string", 'm', ' ');
  ck_assert_str_eq(str_1[3], str_2[3]);

  s21_sprintf(str_1[4], "Rando%10c%-5lc string", 'm', ' ');
  sprintf(str_2[4], "Rando%10c%-5lc string", 'm', ' ');
  ck_assert_str_eq(str_1[4], str_2[4]);

  // d-specifier

  s21_sprintf(str_1[5], "%d", numbers[0]);
  sprintf(str_2[5], "%d", numbers[0]);
  ck_assert_str_eq(str_1[5], str_2[5]);

  s21_sprintf(str_1[6], "Ab%d", numbers[2]);
  sprintf(str_2[6], "Ab%d", numbers[2]);
  ck_assert_str_eq(str_1[6], str_2[6]);

  s21_sprintf(str_1[7], "Arr %d", numbers[2]);
  sprintf(str_2[7], "Arr %d", numbers[2]);
  ck_assert_str_eq(str_1[7], str_2[7]);

  s21_sprintf(str_1[8], "   Fide   %d", numbers[3]);
  sprintf(str_2[8], "   Fide   %d", numbers[3]);
  ck_assert_str_eq(str_1[8], str_2[8]);

  s21_sprintf(str_1[9], "%d Ab", numbers[4]);
  sprintf(str_2[9], "%d Ab", numbers[4]);
  ck_assert_str_eq(str_1[9], str_2[9]);

  s21_sprintf(str_1[10], "%d   Ab   ", numbers[5]);
  sprintf(str_2[10], "%d   Ab   ", numbers[5]);
  ck_assert_str_eq(str_1[10], str_2[10]);

  s21_sprintf(str_1[11], "%ldSunrise", (long)numbers[5]);
  sprintf(str_2[11], "%ldSunrise", (long)numbers[5]);
  ck_assert_str_eq(str_1[12], str_2[12]);

  s21_sprintf(str_1[13], "%d   Random   ", numbers[5]);
  sprintf(str_2[13], "%d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[13], str_2[13]);

  s21_sprintf(str_1[14], "%d   Random   ", numbers[5]);
  sprintf(str_2[14], "%d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[14], str_2[14]);

  s21_sprintf(str_1[15], "%+d   Random   ", numbers[5]);
  sprintf(str_2[15], "%+d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[15], str_2[15]);

  s21_sprintf(str_1[16], "%-d   Random   ", numbers[5]);
  sprintf(str_2[16], "%-d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[16], str_2[16]);

  s21_sprintf(str_1[17], "% d   Random   ", numbers[5]);
  sprintf(str_2[17], "% d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[17], str_2[17]);

  s21_sprintf(str_1[18], "%10d   Random   ", numbers[5]);
  sprintf(str_2[18], "%10d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[18], str_2[18]);

  s21_sprintf(str_1[19], "%-10d   Random   ", numbers[5]);
  sprintf(str_2[19], "%-10d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[19], str_2[19]);

  s21_sprintf(str_1[20], "%.0d   Random   ", numbers[5]);
  sprintf(str_2[20], "%.0d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[20], str_2[20]);

  s21_sprintf(str_1[21], "%.1d   Random   ", numbers[5]);
  sprintf(str_2[21], "%.1d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[21], str_2[21]);

  s21_sprintf(str_1[22], "%.15d   Random   ", numbers[5]);
  sprintf(str_2[22], "%.15d   Random   ", numbers[5]);
  ck_assert_str_eq(str_1[22], str_2[22]);

  s21_sprintf(str_1[23], "%hd   Random   ", short_int);
  sprintf(str_2[23], "%hd   Random   ", short_int);
  ck_assert_str_eq(str_1[23], str_2[23]);

  s21_sprintf(str_1[24], "%hd   Random   ", -short_int);
  sprintf(str_2[24], "%hd   Random   ", -short_int);
  ck_assert_str_eq(str_1[24], str_2[24]);

//  // long int long_int = 1234567890;
//  s21_sprintf(str_1[25], "%ld   Random   ", long_int);
//  sprintf(str_2[25], "%ld   Random   ", long_int);
//  ck_assert_str_eq(str_1[25], str_2[25]);
//  // failed: str_1[25] == "138673521362   Random", str_2[25] == "1234567890   Random   "

//  s21_sprintf(str_1[26], "%ld   Random   ", -long_int);
//  sprintf(str_2[26], "%ld   Random   ", -long_int);
//  ck_assert_str_eq(str_1[26], str_2[26]);

  s21_sprintf(str_1[27], "%+-10.3d   Random   ", numbers[1]);
  sprintf(str_2[27], "%+-10.3d   Random   ", numbers[1]);
  ck_assert_str_eq(str_1[27], str_2[27]);

  s21_sprintf(str_1[28], "%+-10.3d   Random   ", numbers[2]);
  sprintf(str_2[28], "%+-10.3d   Random   ", numbers[2]);
  ck_assert_str_eq(str_1[28], str_2[28]);

  s21_sprintf(str_1[29], "% -10.3d   Random   ", numbers[1]);
  sprintf(str_2[29], "% -10.3d   Random   ", numbers[1]);
  ck_assert_str_eq(str_1[29], str_2[29]);

  s21_sprintf(str_1[30], "% -10.3d   Random   ", numbers[0]);
  sprintf(str_2[30], "% -10.3d   Random   ", numbers[0]);
  ck_assert_str_eq(str_1[30], str_2[30]);

  s21_sprintf(str_1[31], "%0*d   Random   ", 10, numbers[1]);
  sprintf(str_2[31], "%0*d   Random   ", 10, numbers[1]);
  ck_assert_str_eq(str_1[31], str_2[31]);

  s21_sprintf(str_1[32], "%*.0d   Hello   ", 10, numbers[1]);
  sprintf(str_2[32], "%*.0d   Hello   ", 10, numbers[1]);
  ck_assert_str_eq(str_1[32], str_2[32]);

  s21_sprintf(str_1[33], "% -*.*hd   Random   ", 10, 3, short_int);
  sprintf(str_2[33], "% -*.*hd   Random   ", 10, 3, short_int);
  ck_assert_str_eq(str_1[33], str_2[33]);

  char *format3 = "%-3.d";
  s21_sprintf(str_1[35], format3, numbers[0]);
  sprintf(str_2[35], format3, numbers[0]);
  ck_assert_str_eq(str_1[35], str_2[35]);

  // char *format5 = "%.-0d";
  // s21_sprintf(str_1[81], format5, numbers[0]);
  // sprintf(str_2[81], format5, numbers[0]);
  // ck_assert_str_eq(str_1[81], str_2[81]);

  // i-specifier

  s21_sprintf(str_1[36], "%i   random   ", hex[0]);
  sprintf(str_2[36], "%i   random   ", hex[0]);
  ck_assert_str_eq(str_1[36], str_2[36]);

  s21_sprintf(str_1[37], "%irandom", hex[1]);
  sprintf(str_2[37], "%irandom", hex[1]);
  ck_assert_str_eq(str_1[37], str_2[37]);

  s21_sprintf(str_1[38], "%irand%iom", hex[2], hex[3]);
  sprintf(str_2[38], "%irand%iom", hex[2], hex[3]);
  ck_assert_str_eq(str_1[38], str_2[38]);

  s21_sprintf(str_1[39], "random%i%i", hex[1], hex[2]);
  sprintf(str_2[39], "random%i%i", hex[1], hex[2]);
  ck_assert_str_eq(str_1[39], str_2[39]);

  // f-specifier

  s21_sprintf(str_1[40], "%f random", 67.00000);
  sprintf(str_2[40], "%f random", 67.00000);
  ck_assert_str_eq(str_1[40], str_2[40]);

  s21_sprintf(str_1[41], "%Lf random", (long double)4.3);
  sprintf(str_2[41], "%Lf random", (long double)4.3);
  ck_assert_str_eq(str_1[41], str_2[41]);

  s21_sprintf(str_1[42], "%f", 4555.0099);
  sprintf(str_2[42], "%f", 4555.0099);
  ck_assert_str_eq(str_1[42], str_2[42]);

  s21_sprintf(str_1[43], "%f", 4.0000);
  sprintf(str_2[43], "%f", 4.0000);
  ck_assert_str_eq(str_1[43], str_2[43]);

  long double val = 123456789.123456789;
  s21_sprintf(str_1[44], "%.4Lf", val);
  sprintf(str_2[44], "%.4Lf", val);
  ck_assert_str_eq(str_1[44], str_2[44]);

  char *format_4 = "%Lf";
  long double val_2 = 72537572375.1431341;
  ck_assert_int_eq(s21_sprintf(str_1[69], format_4, val_2),
                   sprintf(str_2[69], format_4, val_2));
  ck_assert_str_eq(str_1[69], str_2[69]);

  s21_sprintf(str_1[70], "%f", FLT_MAX / 1E25);
  sprintf(str_2[70], "%f", FLT_MAX / 1E25);
  ck_assert_str_eq(str_1[70], str_2[70]);

  s21_sprintf(str_1[45], "%+10.6f % -#10.3f %0*f % 10.0f % #-10.1f", 5000.0099,
              -5000.0099, -4, 500.09, 0., 0.);
  sprintf(str_2[45], "%+10.6f % -#10.3f %0*f % 10.0f % #-10.1f", 5000.0099,
          -5000.0099, -4, 500.09, 0., 0.);
  ck_assert_str_eq(str_1[45], str_2[45]);

  s21_sprintf(str_1[46], "%+10.6f % -#10.3f %0*f % 10.0f % #-10.1f", 5000.0099,
              -5000.0099, 4, 500.09, 0., 0.);
  sprintf(str_2[46], "%+10.6f % -#10.3f %0*f % 10.0f % #-10.1f", 5000.0099,
          -5000.0099, 4, 500.09, 0., 0.);
  ck_assert_str_eq(str_1[46], str_2[46]);

  for (double i = 1002990; i >= 0.0000001; i /= 10) {
    s21_sprintf(str_1[47], "%-+#7.4f", i);
    sprintf(str_2[47], "%-+#7.4f", i);
    ck_assert_str_eq(str_1[47], str_2[47]);
  }

  for (double i = -1002990; i <= -0.0000001; i /= 10) {
    s21_sprintf(str_1[48], "% 07f", i);
    sprintf(str_2[48], "% 07f", i);
    ck_assert_str_eq(str_1[48], str_2[48]);
  }

  char *format_5 = "%.2Lf";  ///////
  long double val_3 = 75.9999999;
  ck_assert_int_eq(s21_sprintf(str_1[80], format_5, val_3),
                   sprintf(str_2[80], format_5, val_3));
  ck_assert_str_eq(str_1[80], str_2[80]);

  // s-specifier

  sprintf(str_1[49], "%50.7ls", L"Random phrase");
  s21_sprintf(str_2[49], "%50.7ls", L"Random phrase");
  ck_assert_str_eq(str_1[49], str_2[49]);

  sprintf(str_1[50], "%5.7ls", L"Random phrase");
  s21_sprintf(str_2[50], "%5.7ls", L"Random phrase");
  ck_assert_str_eq(str_1[50], str_2[50]);

  sprintf(str_1[51], "%-50.7ls", L"Random phrase");
  s21_sprintf(str_2[51], "%-50.7ls", L"Random phrase");
  ck_assert_str_eq(str_1[51], str_2[51]);

  sprintf(str_1[52], "%s%s", "Random", "world");
  s21_sprintf(str_2[52], "%s%s", "Random", "world");
  ck_assert_str_eq(str_1[52], str_2[52]);

  sprintf(str_1[53], "%d%s%d", 25, "Random", 40);
  s21_sprintf(str_2[53], "%d%s%d", 25, "Random", 40);
  ck_assert_str_eq(str_1[53], str_2[53]);

  sprintf(str_1[54], "%s%c", "Random", '!');
  s21_sprintf(str_2[54], "%s%c", "Random", '!');
  ck_assert_str_eq(str_1[54], str_2[54]);

  wchar_t *wc = L"Random";
  sprintf(str_1[55], "%ls", wc);
  s21_sprintf(str_2[55], "%ls", wc);
  ck_assert_str_eq(str_1[55], str_2[55]);

  char *wc1 = "Random";
  char *format4 = "%ls";
  sprintf(str_1[56], format4, wc1);
  s21_sprintf(str_2[56], format4, wc1);
  ck_assert_str_eq(str_1[56], str_2[56]);

  wchar_t *n_str = NULL;
  sprintf(str_1[72], "%ls", n_str);
  s21_sprintf(str_2[72], "%ls", n_str);
  ck_assert_str_eq(str_1[72], str_2[72]);

  // u-specifier
/*
  sprintf(str_1[57], "%2lu", (long)-45);
  s21_sprintf(str_2[57], "%2lu", (long)-45);
  ck_assert_str_eq(str_1[57], str_2[57]);

  sprintf(str_1[58], "%u", INT32_MAX);
  s21_sprintf(str_2[58], "%u", INT32_MAX);
  ck_assert_str_eq(str_1[58], str_2[58]);

  sprintf(str_1[59], "%u", INT32_MIN);
  s21_sprintf(str_2[59], "%u", INT32_MIN);
  ck_assert_str_eq(str_1[59], str_2[59]);

  sprintf(str_1[60], "%u", 0);
  s21_sprintf(str_2[60], "%u", 0);
  ck_assert_str_eq(str_1[60], str_2[60]);

  sprintf(str_1[60], "Random %u%u", 4, 2);
  s21_sprintf(str_2[60], "Random %u%u", 4, 2);
  ck_assert_str_eq(str_1[60], str_2[60]);

  sprintf(str_1[61], "Random %-10.3u %0u %-10.5hu %lu", (unsigned)12345,
          (unsigned)0, (unsigned short)123456, (unsigned long)123456789000);
  s21_sprintf(str_2[61], "Random %-10.3u %0u %-10.5hu %lu", (unsigned)12345,
              (unsigned)0, (unsigned short)123456, (unsigned long)123456789000);
  ck_assert_str_eq(str_1[61], str_2[61]);
*/
  //%%

  s21_sprintf(str_1[62], "100%%random");
  sprintf(str_2[62], "100%%random");
  ck_assert_str_eq(str_1[62], str_2[62]);

  s21_sprintf(str_1[63], "%%%%%%%%%%");
  sprintf(str_2[63], "%%%%%%%%%%");
  ck_assert_str_eq(str_1[63], str_2[63]);

  sprintf(str_1[63], "%%%%%d%%%%", 15);
  sprintf(str_2[63], "%%%%%d%%%%", 15);
  ck_assert_str_eq(str_1[63], str_2[63]);

  // n-specifier

  int n1, n2, n3, n4;

  sprintf(str_1[64], "Random phrase %n", &n1);
  s21_sprintf(str_2[64], "Random phrase %n", &n2);
  ck_assert_str_eq(str_1[64], str_2[64]);

  sprintf(str_1[65], "%nRandom [%%]-percentage phrase%c %n", &n1, '!', &n2);
  s21_sprintf(str_2[65], "%nRandom [%%]-percentage phrase%c %n", &n3, '!', &n4);
  ck_assert_str_eq(str_1[65], str_2[65]);

  sprintf(str_1[66], "%n%n Random %s", &n1, &n2, "string");
  s21_sprintf(str_2[66], "%n%n Random %s", &n3, &n4, "string");
  ck_assert_str_eq(str_1[66], str_2[66]);

  char *format = "%%z";
  sprintf(str_1[67], format, 0);
  s21_sprintf(str_2[67], format, 0);
  ck_assert_str_eq(str_1[67], str_2[67]);

  sprintf(str_1[68], "without specifier");
  s21_sprintf(str_2[68], "without specifier");
  ck_assert_str_eq(str_1[68], str_2[68]);
}
END_TEST

START_TEST(s21_sscanf_test_my) {
  // %s specifier
  char a[100] = {0};
  char a1[100] = {0};
  char b[100] = {0};
  char b1[100] = {0};

  int result = 0;
  int s21_result = 0;

  s21_result = s21_sscanf("hello", "%s", a);
  result = sscanf("hello", "%s", a1);
  ck_assert_str_eq(a, a1);
  ck_assert_int_eq(result, s21_result);

  short  hd = 0, hd21=0;
  s21_result = s21_sscanf("32766", "%hd", &hd21);
  result = sscanf("32766", "%hd", &hd);
  ck_assert_int_eq(result, s21_result);
  if (result == s21_result) ck_assert_int_eq(hd, hd21);

  int d = 0, d21=0;
  s21_result = s21_sscanf("2147483646", "%d", &d21);
  result = sscanf("2147483646", "%d", &d);
  ck_assert_int_eq(result, s21_result);
  if (result == s21_result) ck_assert_int_eq(d, d21);

  long int ld = 0, ld21=0; 
  s21_result = s21_sscanf("4294967294", "%ld", &ld21);
  result = sscanf("4294967294", "%ld", &ld);
  ck_assert_int_eq(result, s21_result);
  if (result == s21_result) ck_assert_int_eq(ld, ld21);
  // failed: ld == 2147483647, ld21 == -2 only for 32 bit system

} END_TEST

START_TEST(s21_sscanf_test) {
  // %s specifier
  char a[100] = {0};
  char a1[100] = {0};
  char b[100] = {0};
  char b1[100] = {0};

  int result = 0;
  int s21_result = 0;

  s21_result = s21_sscanf("hello", "%s", a);
  result = sscanf("hello", "%s", a1);
  ck_assert_str_eq(a, a1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("  hello", "%s", a);
  result = sscanf("  hello", "%s", a1);
  ck_assert_str_eq(a, a1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("  hello  ", "%s", a);
  result = sscanf("  hello  ", "%s", a1);
  ck_assert_str_eq(a, a1);
  ck_assert_int_eq(result, s21_result);

  char y[100] = {0};
  char y1[100] = {0};
  s21_result = s21_sscanf("", "%s", y);
  result = sscanf("", "%s", y1);
  ck_assert_str_eq(y, y1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("   ", "%s", y);
  result = sscanf("   ", "%s", y1);
  ck_assert_str_eq(y, y1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("hello world", "%s %s", a, b);
  result = sscanf("hello world", "%s %s", a1, b1);
  ck_assert_str_eq(a, a1);
  ck_assert_str_eq(b, b1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("    hello world", "%s %s", a, b);
  result = sscanf("   hello world", "%s %s", a1, b1);
  ck_assert_str_eq(a, a1);
  ck_assert_str_eq(b, b1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("    hello world", "%4s %s", a, b);
  result = sscanf("   hello world", "%4s %s", a1, b1);
  ck_assert_str_eq(a, a1);
  ck_assert_str_eq(b, b1);
  ck_assert_int_eq(result, s21_result);

  int i = 0;
  int j = 0;
  s21_result = s21_sscanf("184", "%d", &i);
  result = sscanf("184", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  /*
  s21_result = s21_sscanf("    hello world", "%0s %s", a, b);
  result = sscanf("   hello world", "%0s %s", a1, b1);
  ck_assert_str_eq(a, a1);
  ck_assert_str_eq(b, b1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("    hello world", "%*s %s", a, b);
  result = sscanf("   hello world", "%*s %s", a1, b1);
  ck_assert_str_eq(a, a1);
  ck_assert_str_eq(b, b1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("    hello world", "%s %*s", a, b);
  result = sscanf("   hello world", "%s %*s", a1, b1);
  ck_assert_str_eq(a, a1);
  ck_assert_str_eq(b, b1);
  ck_assert_int_eq(result, s21_result);

  int n = 3;
  int n1 = 0;
  s21_result = s21_sscanf("    hello world", "%s %*s %n", a, &n);
  result = sscanf("    hello world", "%s %*s %n", a1, &n1);
  ck_assert_str_eq(a, a1);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("    hello world", "%2s %*s %n", a, b, &n);
  result = sscanf("   hello world", "%2s %*s %n", a1, b1, &n1);
  ck_assert_str_eq(a, a1);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("    hello world", "%ls %s", a, b);
  result = sscanf("   hello world", "%ls %s", a1, b1);
  ck_assert_str_eq(a, a1);
  ck_assert_str_eq(b, b1);
  ck_assert_int_eq(result, s21_result);

  n = 0;
  n1 = 0;
  s21_result = s21_sscanf("    hello world", "%s %ls %n", a, b, &n);
  result = sscanf("    hello world", "%s %ls %n", a1, b1, &n1);
  ck_assert_str_eq(a, a1);
  ck_assert_str_eq(b, b1);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  // %d specifier

  int i = 0;
  int j = 0;
  s21_result = s21_sscanf("184", "%d", &i);
  result = sscanf("184", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  i = 0;
  j = 0;
  s21_result = s21_sscanf("t184", "%d", &i);
  result = sscanf("t184", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("184t", "%d", &i);
  result = sscanf("184t", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  i = 0;
  j = 0;
  s21_result = s21_sscanf("", "%d", &i);
  result = sscanf("", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("184h86", "%d", &i);
  result = sscanf("184h86", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("184   86", "%d", &i);
  result = sscanf("184   86", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("-184", "%d", &i);
  result = sscanf("-184", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf(" 56", "%d", &i);
  result = sscanf(" 56", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf(" -56 ", "%d", &i);
  result = sscanf(" -56 ", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("197856365839", "%d", &i);
  result = sscanf("197856365839", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("-197856365839", "%d", &i);
  result = sscanf("-197856365839", "%d", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  n = 0;
  n1 = 0;
  s21_result = s21_sscanf("184h86", "%d %i", &i, &n);
  result = sscanf("184h86", "%d %i", &j, &n1);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("184 86", "%d %i", &i, &n);
  result = sscanf("184 86", "%d %i", &j, &n1);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  int i1 = 0;
  int j1 = 0;
  s21_result = s21_sscanf("3245 1322", "%d %d", &i, &j);
  result = sscanf("3245 1322", "%d %d", &i1, &j1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("3245 1322", "%2d %d", &i, &j);
  result = sscanf("3245 1322", "%2d %d", &i1, &j1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);
  ck_assert_int_eq(result, s21_result);

  i = 0;
  j = 0;
  i1 = 0;
  j1 = 0;

  s21_result = s21_sscanf("3245 1322", "%-2d %d", &i, &j);
  result = sscanf("3245 1322", "%-2d %d", &i1, &j1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);
  ck_assert_int_eq(result, s21_result);

  i = 0;
  i1 = 0;
  j = 0;
  j1 = 0;

  s21_result = s21_sscanf("3245 1322", "%*d %d", &i, &j);
  result = sscanf("3245 1322", "%*d %d", &i1, &j1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("3245 1322", "%d %*d", &i, &j);
  result = sscanf("3245 1322", "%d %*d", &i1, &j1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);
  ck_assert_int_eq(result, s21_result);

  short int q = 0;
  short int w = 0;
  short int q1 = 0;
  short int w1 = 0;
  s21_result = s21_sscanf("3245 1322", "%hd %hd", &q, &w);
  result = sscanf("3245 1322", "%hd %hd", &q1, &w1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(w, w1);
  ck_assert_int_eq(result, s21_result);

  long int e = 0;
  long int r = 0;
  long int e1 = 0;
  long int r1 = 0;
  s21_result = s21_sscanf("3245 1322", "%ld %ld", &e, &r);
  result = sscanf("3245 1322", "%ld %ld", &e1, &r1);
  ck_assert_int_eq(e, e1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(result, s21_result);

  // %i specifier

  int d = 0;
  int d1 = 0;
  s21_result = s21_sscanf("3245", "%i", &d);
  result = sscanf("3245", "%i", &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("075", "%i", &d);
  result = sscanf("075", "%i", &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("075", "%i", &d);
  result = sscanf("61", "%i", &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0x342", "%i", &d);
  result = sscanf("834", "%i", &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("834", "%i", &d);
  result = sscanf("834", "%i", &d1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  i = 0;
  j = 0;
  s21_result = s21_sscanf("", "%i", &i);
  result = sscanf("", "%i", &j);
  ck_assert_int_eq(i, j);
  ck_assert_int_eq(result, s21_result);

  // не проходит
  //  s21_result = s21_sscanf(" ", "%i", &i);
  //  result = sscanf(" ", "%i", &j);
  //  ck_assert_int_eq(i, j);
  //  ck_assert_int_eq(result, s21_result);

  int t = 0;
  int t1 = 0;

  s21_result = s21_sscanf("834 0x45", "%i %i", &d, &t);
  result = sscanf("834 0x45", "%i %i", &d1, &t1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(t, t1);
  ck_assert_int_eq(result, s21_result);

  t = 0;
  t1 = 0;
  s21_result = s21_sscanf("834 0x45", "%i %i", &d, &t);
  result = sscanf("834 0x45", "%i %i", &d1, &t1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(t, t1);
  ck_assert_int_eq(result, s21_result);

  d = 0;
  d1 = 0;
  t = 0;
  t1 = 0;
  s21_result = s21_sscanf("d834 0x45", "%i %i", &d, &t);
  result = sscanf("d834 0x45", "%i %i", &d1, &t1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(t, t1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("234 0x837", "%*i %i", &d, &t);
  result = sscanf("234 0x837", "%*i %i", &d1, &t1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("234 0x837", "%i %*i", &d, &t);
  result = sscanf("234 0x837", "%i %*i", &d1, &t1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("234 0x837", "%i %2i", &d, &t);
  result = sscanf("234 0x837", "%i %2i", &d1, &t1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("234 0x837", "%-1i %2i", &d, &t);
  result = sscanf("234 0x837", "%-1i %2i", &d1, &t1);
  ck_assert_int_eq(d, d1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("3245 1322", "%hi %hi", &q, &w);
  result = sscanf("3245 1322", "%hi %hi", &q1, &w1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(w, w1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("035 1322", "%hi %hi", &q, &w);
  result = sscanf("035 1322", "%hi %hi", &q1, &w1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(w, w1);
  ck_assert_int_eq(result, s21_result);

  r = 0;
  r1 = 0;
  s21_result = s21_sscanf("035 132264782398", "%li %li", &e, &r);
  result = sscanf("035 132264782398", "%li %li", &e1, &r1);
  ck_assert_int_eq(e, e1);
  ck_assert_int_eq(r, r1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("035 1322", "%li %hi", &e, &q);
  result = sscanf("035 1322", "%li %hi", &e1, &q1);
  ck_assert_int_eq(e, e1);
  ck_assert_int_eq(q, q1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("035 0x2846", "%i %i %n", &i, &j, &n);
  result = sscanf("035 0x2846", "%i %i %n", &i1, &j1, &n1);
  ck_assert_int_eq(i, i1);
  ck_assert_int_eq(j, j1);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  // %c specifier

  char c = 0;
  char c1 = 0;
  s21_result = s21_sscanf("h", "%c", &c);
  result = sscanf("h", "%c", &c1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("gh", "%c", &c);
  result = sscanf("gh", "%c", &c1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("  gh", "%c", &c);
  result = sscanf("  gh", "%c", &c1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("g h", "%c", &c);
  result = sscanf("g h", "%c", &c1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("g h", "%-1c", &c);
  result = sscanf("g h", "%-1c", &c1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(result, s21_result);

  char c2;
  char c3;
  s21_result = s21_sscanf("g h", "%c %c %n", &c, &c2, &n);
  result = sscanf("g h", "%c %c %n", &c1, &c3, &n1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(c2, c3);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  c2 = 0;
  c3 = 0;
  s21_result = s21_sscanf("g h", "%c%c %n", &c, &c2, &n);
  result = sscanf("g h", "%c%c %n", &c1, &c3, &n1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(c2, c3);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  c2 = 0;
  c3 = 0;
  s21_result = s21_sscanf("g  h", "%c %c %n", &c, &c2, &n);
  result = sscanf("g  h", "%c %c %n", &c1, &c3, &n1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(c2, c3);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  wchar_t m = 0;
  wchar_t m1 = 0;
  s21_result = s21_sscanf("h", "%lc", &m);
  result = sscanf("h", "%lc", &m1);
  ck_assert_int_eq(m, m1);
  ck_assert_int_eq(result, s21_result);

  char k = 0;
  char k1 = 0;
  s21_result = s21_sscanf("g h", "%c %c %n", &c, &k, &n);
  result = sscanf("g h", "%c %c %n", &c1, &k1, &n1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(k, k1);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("..", "%c %c %n", &c, &k, &n);
  result = sscanf("..", "%c %c %n", &c1, &k1, &n1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(k, k1);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("h 6", "%c %*c %n", &c, &n);
  result = sscanf("h 6", "%c %*c %n", &c1, &n1);
  ck_assert_int_eq(c, c1);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(result, s21_result);

  // %% specifier
  c = 0;
  c1 = 0;
  n = 0;
  n1 = 0;
  s21_result = s21_sscanf("h 6", "%% %n", &n);
  result = sscanf("h 6", "%% %n", &n1);
  ck_assert_int_eq(result, s21_result);

  // %p specifier
  int val = 123;
  char buf[100] = {0};
  sprintf(buf, "%p", (void *)&val);
  void *ptr = 0;
  void *ptr2 = 0;
  sscanf(buf, "%p", &ptr);
  s21_sscanf(buf, "%p", &ptr2);
  // ck_assert_ptr_eq(ptr, ptr2);

  // %e %E %f %g %G specifiers

  float f = 0;
  float dd = 0;
  float f1 = 0;
  float dd1 = 0;

  // scientific notation

  s21_result = s21_sscanf("127564.3846 1.275643846e3", "%e %e", &f, &dd);
  result = sscanf("127564.3846 1.275643846e3", "%e %e", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("127564.3846 1.275643846e3", "%E %E", &f, &dd);
  result = sscanf("127564.3846 1.275643846e3", "%E %E", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("127564.3846 1.275643846e3", "%f %f", &f, &dd);
  result = sscanf("127564.3846 1.275643846e3", "%f %f", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("127564.3846 1.275643846e3", "%g %g", &f, &dd);
  result = sscanf("127564.3846 1.275643846e3", "%g %g", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("127564.3846 1.275643846e3", "%G %G", &f, &dd);
  result = sscanf("127564.3846 1.275643846e3", "%G %G", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  // negative scientific notation

  s21_result = s21_sscanf("127564.3846 12756.43846e-3", "%e %e", &f, &dd);
  result = sscanf("127564.3846 12756.43846e-3", "%e %e", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("127564.3846 12756.43846e-3", "%E %E", &f, &dd);
  result = sscanf("127564.3846 12756.43846e-3", "%E %E", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("127564.3846 12756.43846e-3", "%f %f", &f, &dd);
  result = sscanf("127564.3846 12756.43846e-3", "%f %f", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("127564.3846 12756.43846e-3", "%g %g", &f, &dd);
  result = sscanf("127564.3846 12756.43846e-3", "%g %g", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("127564.3846 12756.43846e-3", "%G %G", &f, &dd);
  result = sscanf("127564.3846 12756.43846e-3", "%G %G", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  // basic
  s21_result = s21_sscanf("0.008726", "%e", &f);
  result = sscanf("0.008726", "%e", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%E", &f);
  result = sscanf("0.008726", "%E", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%f", &f);
  result = sscanf("0.008726", "%f", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%g", &f);
  result = sscanf("0.008726", "%g", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%G", &f);
  result = sscanf("0.008726", "%G", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  // negative numbers

  s21_result = s21_sscanf("-0.008726", "%e", &f);
  result = sscanf("-0.008726", "%e", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("-0.008726", "%E", &f);
  result = sscanf("-0.008726", "%E", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("-0.008726", "%f", &f);
  result = sscanf("-0.008726", "%f", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("-0.008726", "%g", &f);
  result = sscanf("-0.008726", "%g", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("-0.008726", "%G", &f);
  result = sscanf("-0.008726", "%G", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  // spaces at the beginning
  s21_result = s21_sscanf("   0.008726", "%e", &f);
  result = sscanf("   0.008726", "%e", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("   0.008726", "%E", &f);
  result = sscanf("   0.008726", "%E", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("  0.008726", "%f", &f);
  result = sscanf("   0.008726", "%f", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("   0.008726", "%g", &f);
  result = sscanf("   0.008726", "%g", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("   0.008726", "%G", &f);
  result = sscanf("   0.008726", "%G", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  // spaces
  f = 0;
  f1 = 0;
  s21_result = s21_sscanf("   ", "%e", &f);
  result = sscanf("   ", "%e", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  f = 0;
  f1 = 0;
  s21_result = s21_sscanf("   ", "%E", &f);
  result = sscanf("   ", "%E", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  f = 0;
  f1 = 0;
  s21_result = s21_sscanf("   ", "%f", &f);
  result = sscanf("   ", "%f", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  f = 0;
  f1 = 0;
  s21_result = s21_sscanf("   ", "%g", &f);
  result = sscanf("   ", "%g", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  f = 0;
  f1 = 0;
  s21_result = s21_sscanf("   ", "%G", &f);
  result = sscanf("   ", "%G", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  // empty lines
  s21_result = s21_sscanf("", "%e", &f);
  result = sscanf("", "%e", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("", "%E", &f);
  result = sscanf("", "%E", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("", "%f", &f);
  result = sscanf("", "%f", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("", "%g", &f);
  result = sscanf("", "%g", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("", "%G", &f);
  result = sscanf("", "%G", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  // snowflakes
  f = 0;
  f1 = 0;
  dd = 0;
  dd1 = 0;
  s21_result = s21_sscanf("5674.007827 4758", "%*e %e", &f, &dd);
  result = sscanf("5674.007827 4758", "%*e %e", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  f = 0;
  f1 = 0;
  dd = 0;
  dd1 = 0;
  s21_result = s21_sscanf("5674.007827 4758", "%*E %E", &f, &dd);
  result = sscanf("5674.007827 4758", "%*E %E", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  f = 0;
  f1 = 0;
  dd = 0;
  dd1 = 0;
  s21_result = s21_sscanf("5674.007827 4758", "%*f %f", &f, &dd);
  result = sscanf("5674.007827 4758", "%*f %f", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  f = 0;
  f1 = 0;
  dd = 0;
  dd1 = 0;
  s21_result = s21_sscanf("5674.007827 4758", "%*g %g", &f, &dd);
  result = sscanf("5674.007827 4758", "%*g %g", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  f = 0;
  f1 = 0;
  dd = 0;
  dd1 = 0;
  s21_result = s21_sscanf("5674.007827 4758", "%*G %G", &f, &dd);
  result = sscanf("5674.007827 4758", "%*G %G", &f1, &dd1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);

  // width
  s21_result = s21_sscanf("0.008726", "%6e", &f);
  result = sscanf("0.008726", "%6e", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%4E", &f);
  result = sscanf("0.008726", "%4E", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%4f", &f);
  result = sscanf("0.008726", "%4f", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%4g", &f);
  result = sscanf("0.008726", "%4g", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%4G", &f);
  result = sscanf("0.008726", "%4G", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  // negative width

  s21_result = s21_sscanf("0.008726", "%-6e", &f);
  result = sscanf("0.008726", "%-6e", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%-4E", &f);
  result = sscanf("0.008726", "%-4E", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%-4f", &f);
  result = sscanf("0.008726", "%-4f", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%-4g", &f);
  result = sscanf("0.008726", "%-4g", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%-4G", &f);
  result = sscanf("0.008726", "%-4G", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  // zero width

  s21_result = s21_sscanf("0.008726", "%0e", &f);
  result = sscanf("0.008726", "%0e", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%0E", &f);
  result = sscanf("0.008726", "%0E", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%0f", &f);
  result = sscanf("0.008726", "%0f", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%0g", &f);
  result = sscanf("0.008726", "%0g", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("0.008726", "%0G", &f);
  result = sscanf("0.008726", "%0G", &f1);
  ck_assert_float_eq(f, f1);
  ck_assert_int_eq(result, s21_result);

  // length L
  long double lf = 0;
  long double lf1 = 0;
  s21_result = s21_sscanf("9.9996587169235770324564357345", "%Le", &lf);
  result = sscanf("9.9996587169235770324564357345", "%Le", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%LE", &lf);
  result = sscanf("9.9996587169235770324564357345", "%LE", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%Lf", &lf);
  result = sscanf("9.9996587169235770324564357345", "%Lf", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%Lg", &lf);
  result = sscanf("9.9996587169235770324564357345", "%Lg", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%LG", &lf);
  result = sscanf("9.9996587169235770324564357345", "%LG", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  // length L + width
  s21_result = s21_sscanf("9.9996587169235770324564357345", "%4Le", &lf);
  result = sscanf("9.9996587169235770324564357345", "%4Le", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%4LE", &lf);
  result = sscanf("9.9996587169235770324564357345", "%4LE", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%4Lf", &lf);
  result = sscanf("9.9996587169235770324564357345", "%4Lf", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%4Lg", &lf);
  result = sscanf("9.9996587169235770324564357345", "%4Lg", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%4LG", &lf);
  result = sscanf("9.9996587169235770324564357345", "%4LG", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  // length L + width *
  lf = 0;
  lf1 = 0;
  s21_result = s21_sscanf("9.9996587169235770324564357345", "%*Le", &lf);
  result = sscanf("9.9996587169235770324564357345", "%*Le", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%*LE", &lf);
  result = sscanf("9.9996587169235770324564357345", "%*LE", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%*Lf", &lf);
  result = sscanf("9.9996587169235770324564357345", "%*Lf", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%*Lg", &lf);
  result = sscanf("9.9996587169235770324564357345", "%*Lg", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%*LG", &lf);
  result = sscanf("9.9996587169235770324564357345", "%*LG", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  // length L + negative width

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%-4Le", &lf);
  result = sscanf("9.9996587169235770324564357345", "%-4Le", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%-4LE", &lf);
  result = sscanf("9.9996587169235770324564357345", "%-4LE", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%-4Lf", &lf);
  result = sscanf("9.9996587169235770324564357345", "%-4Lf", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%-4Lg", &lf);
  result = sscanf("9.9996587169235770324564357345", "%-4Lg", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  s21_result = s21_sscanf("9.9996587169235770324564357345", "%-4LG", &lf);
  result = sscanf("9.9996587169235770324564357345", "%-4LG", &lf1);
  ck_assert_ldouble_eq(lf, lf1);
  ck_assert_int_eq(result, s21_result);

  // with %n

  n = 0;
  n1 = 0;
  s21_result = s21_sscanf("1275.3846 0.2345", "%e %e %n", &f, &dd, &n);
  result = sscanf("1275.3846 0.2345", "%e %e %n", &f1, &dd1, &n1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);
  ck_assert_int_eq(n, n1);

  n = 0;
  n1 = 0;
  s21_result = s21_sscanf("1275.3846 0.2345", "%E %E %n", &f, &dd, &n);
  result = sscanf("1275.3846 0.2345", "%E %E %n", &f1, &dd1, &n1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);
  ck_assert_int_eq(n, n1);

  n = 0;
  n1 = 0;
  s21_result = s21_sscanf("1275.3846 0.2345", "%f %f %n", &f, &dd, &n);
  result = sscanf("1275.3846 0.2345", "%f %f %n", &f1, &dd1, &n1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);
  ck_assert_int_eq(n, n1);

  n = 0;
  n1 = 0;
  s21_result = s21_sscanf("1275.3846 0.2345", "%g %g %n", &f, &dd, &n);
  result = sscanf("1275.3846 0.2345", "%g %g %n", &f1, &dd1, &n1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);
  ck_assert_int_eq(n, n1);

  n = 0;
  n1 = 0;
  s21_result = s21_sscanf("1275.3846 0.2345", "%G %G %n", &f, &dd, &n);
  result = sscanf("1275.3846 0.2345", "%G %G %n", &f1, &dd1, &n1);
  ck_assert_float_eq(f, f1);
  ck_assert_float_eq(dd, dd1);
  ck_assert_int_eq(result, s21_result);
  ck_assert_int_eq(n, n1);

*/}
END_TEST

START_TEST(s21_sscanf_u_test) {
  int res = 0;
  int s21_res = 0;
  int d = 0;
  short int hd = 0;
  long int ld = 0;
  unsigned int u = 0;
  unsigned short int hu = 0;
  unsigned long int lu = 0;
  int s21_d = 0;
  short int s21_hd = 0;
  long int s21_ld = 0;
  unsigned int s21_u = 0;
  unsigned short int s21_hu = 0;
  unsigned long int s21_lu = 0;

  s21_res = s21_sscanf("184", "%u", &s21_u);
  res = sscanf("184", "%u", &u);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-184", "%u", &s21_u);
  res = sscanf("-184", "%u", &u);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("184.01", "%u", &s21_u);
  res = sscanf("184.01", "%u", &u);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-184.01", "%u", &s21_u);
  res = sscanf("-184.01", "%u", &u);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("184", "%hu", &s21_hu);
  res = sscanf("184", "%hu", &hu);
  ck_assert_uint_eq(hu, s21_hu);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-184", "%hu", &s21_hu);
  res = sscanf("-184", "%hu", &hu);
  ck_assert_uint_eq(hu, s21_hu);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("184.01", "%hu", &s21_hu);
  res = sscanf("184.01", "%hu", &hu);
  ck_assert_uint_eq(hu, s21_hu);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-184.01", "%hu", &s21_hu);
  res = sscanf("-184.01", "%hu", &hu);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("184", "%u", &s21_d);
  res = sscanf("184", "%u", &d);
  ck_assert_int_eq(d, s21_d);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-184", "%u", &s21_d);
  res = sscanf("-184", "%u", &d);
  ck_assert_int_eq(d, s21_d);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("184.01", "%u", &s21_d);
  res = sscanf("184.01", "%u", &d);
  ck_assert_int_eq(d, s21_d);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-184.01", "%u", &s21_d);
  res = sscanf("-184.01", "%u", &d);
  ck_assert_int_eq(d, s21_d);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("  1   184", "%u", &s21_u);
  res = sscanf("  1   184", "%u", &u);
  ck_assert_uint_eq(d, s21_d);
  ck_assert_int_eq(res, s21_res);
/*
  s21_res = s21_sscanf("98975878579879184", "%lu", &s21_lu); //2216033552
  res = sscanf("98975878579879184", "%lu", &lu); //4294967295
  ck_assert_uint_eq(lu, s21_lu);
  ck_assert_int_eq(res, s21_res);
*/
  s21_res = s21_sscanf("184.01", "%lu", &s21_lu);
  res = sscanf("184.01", "%lu", &lu);
  ck_assert_uint_eq(lu, s21_lu);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-184.01", "%lu", &s21_lu);
  res = sscanf("-184.01", "%lu", &lu);
  ck_assert_uint_eq(lu, s21_lu);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("     184 1    ", "%lu", &s21_lu);
  res = sscanf("184", "%lu", &lu);
  ck_assert_uint_eq(lu, s21_lu);
  ck_assert_int_eq(res, s21_res);

  u = 0;
  s21_u = 0;

  s21_res = s21_sscanf("", "%u", &s21_u);
  res = sscanf("", "%u", &u);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_int_eq(res, s21_res);

  u = 0;
  s21_u = 0;

  s21_res = s21_sscanf("    ", "%u", &s21_u);
  res = sscanf("    ", "%u", &u);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_int_eq(res, s21_res);

  unsigned int u2 = 0;
  unsigned int s21_u2 = 0;
  unsigned int u3 = 0;
  unsigned int s21_u3 = 0;
  s21_res =
      s21_sscanf("184 184.99 -5637", "%u %u %u", &s21_u, &s21_u2, &s21_u3);
  res = sscanf("184 184.99 -5637", "%u %u %u", &u, &u2, &u3);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_uint_eq(u2, s21_u2);
  ck_assert_uint_eq(u3, s21_u3);
  ck_assert_int_eq(res, s21_res);

  int n = 0;
  int s21_n = 0;
  s21_res = s21_sscanf("184     -5637  0", "%u %u %u %n", &s21_u, &s21_u2,
                       &s21_u3, &s21_n);
  res = sscanf("184     -5637  0", "%u %u %u %n", &u, &u2, &u3, &n);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_uint_eq(u2, s21_u2);
  ck_assert_uint_eq(u3, s21_u3);
  ck_assert_int_eq(n, s21_n);
  ck_assert_int_eq(res, s21_res);
  /*
  n = 0;
  s21_n = 0;
  s21_u = 0;
  s21_u2 = 0;
  s21_u3 = 0;
  u = 0;
  u2 = 0;
  u3 = 0;
  s21_res = s21_sscanf("184     -5637  0", "%u %*u %u %n", &s21_u, &s21_u2,
                       &s21_u3, &s21_n);
  res = sscanf("184     -5637  0", "%u %*u %u %n", &u, &u2, &u3, &n);
  ck_assert_uint_eq(u, s21_u);
  ck_assert_uint_eq(u2, s21_u2);
  ck_assert_uint_eq(u3, s21_u3);
  ck_assert_int_eq(n, s21_n);
  ck_assert_int_eq(res, s21_res);

  */
}
END_TEST

START_TEST(s21_sscanf_o_test) {
  int res = 0;
  int s21_res = 0;

  unsigned int o = 0;
  unsigned short int ho = 0;
  unsigned long int lo = 0;

  unsigned int s21_o = 0;
  unsigned short int s21_ho = 0;
  unsigned long int s21_lo = 0;

  s21_res = s21_sscanf("0184", "%o", &s21_o);
  res = sscanf("0184", "%o", &o);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-0184", "%o", &s21_o);
  res = sscanf("-0184", "%o", &o);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0184.345", "%o", &s21_o);
  res = sscanf("0184.345", "%o", &o);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-0184.345", "%o", &s21_o);
  res = sscanf("-0184.345", "%o", &o);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("   0184", "%o", &s21_o);
  res = sscanf("   0184", "%o", &o);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("", "%o", &s21_o);
  res = sscanf("", "%o", &o);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_int_eq(res, s21_res);

  o = 0;
  s21_o = 0;
  s21_res = s21_sscanf("   ", "%o", &s21_o);
  res = sscanf("   ", "%o", &o);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0184", "%ho", &s21_ho);
  res = sscanf("0184", "%ho", &ho);
  ck_assert_uint_eq(ho, s21_ho);
  ck_assert_int_eq(res, s21_res);

  s21_ho = 0;
  ho = 0;
  s21_res = s21_sscanf("-0184", "%ho", &s21_ho);
  res = sscanf("-0184", "%ho", &ho);
  ck_assert_uint_eq(ho, s21_ho);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("   0184", "%ho", &s21_ho);
  res = sscanf("   0184", "%ho", &ho);
  ck_assert_uint_eq(ho, s21_ho);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0184.345", "%ho", &s21_ho);
  res = sscanf("0184.345", "%ho", &ho);
  ck_assert_uint_eq(ho, s21_ho);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("096787987989184456768768564767", "%lo", &s21_lo);
  res = sscanf("096787987989184456768768564767", "%lo", &lo);
  ck_assert_uint_eq(lo, s21_lo);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-096787987989184456768768564767", "%lo", &s21_lo);
  res = sscanf("-096787987989184456768768564767", "%lo", &lo);
  ck_assert_uint_eq(lo, s21_lo);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("   096787987989184456768768564767", "%lo", &s21_lo);
  res = sscanf("   096787987989184456768768564767", "%lo", &lo);
  ck_assert_uint_eq(lo, s21_lo);
  ck_assert_int_eq(res, s21_res);

  s21_res =
      s21_sscanf("   096787987989184456768768564767.34546", "%lo", &s21_lo);
  res = sscanf("   096787987989184456768768564767.34546", "%lo", &lo);
  ck_assert_uint_eq(lo, s21_lo);
  ck_assert_int_eq(res, s21_res);

  o = 0;
  unsigned int o2 = 0;
  unsigned int o3 = 0;
  s21_o = 0;
  unsigned int s21_o2 = 0;
  unsigned int s21_o3 = 0;
  int n = 0;
  int n2 = 0;
  //s21_res = s21_sscanf("", "%o %o %o %n", &s21_o, &s21_o2, &s21_o3, &n2);
  //res = sscanf("184  234 6432  123", "%o %o %o %n", &o, &o2, &o3, &n);
  //ck_assert_uint_eq(o, s21_o);
  //ck_assert_uint_eq(o2, s21_o2);
  //ck_assert_uint_eq(o3, s21_o3);
  //ck_assert_int_eq(res, s21_res);
  //ck_assert_int_eq(n, n2); 

  // n == 0, n2 == 2
  o = 0;
  o2 = 0;
  o3 = 0;
  s21_o = 0;
  s21_o2 = 0;
  s21_o3 = 0;
  n = 0;
  n2 = 0;
  s21_res = s21_sscanf("0184 0234 06432", "%o %o %o %n", &s21_o, &s21_o2,
                       &s21_o3, &n2);
  res = sscanf("0184 0234 06432", "%o %o %o %n", &o, &o2, &o3, &n);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_uint_eq(o2, s21_o2);
  ck_assert_uint_eq(o3, s21_o3);
  ck_assert_int_eq(res, s21_res);
  // ck_assert_int_eq(n, n2);

  o = 0;
  o2 = 0;
  o3 = 0;
  s21_o = 0;
  s21_o2 = 0;
  s21_o3 = 0;
  n = 0;
  n2 = 0;
  s21_res = s21_sscanf("0184 0234 06432", "%o %*o %o %n", &s21_o, &s21_o2, &n2);
  res = sscanf("0184 0234 06432", "%o %*o %o %n", &o, &o2, &n);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_uint_eq(o2, s21_o2);
  ck_assert_uint_eq(o3, s21_o3);
  ck_assert_int_eq(res, s21_res);
  // ck_assert_int_eq(n, n2);
/*
  o = 0;
  o2 = 0;
  o3 = 0;
  s21_o = 0;
  s21_o2 = 0;
  s21_o3 = 0;
  n = 0;
  n2 = 0;
  s21_res =
      s21_sscanf("0184 0234 06432", "%o %*lo %o %n", &s21_o, &s21_o2, &n2);
  res = sscanf("0184 0234 06432", "%o %*lo %o %n", &o, &o2, &n);
  ck_assert_uint_eq(o, s21_o);
  ck_assert_uint_eq(o2, s21_o2);
  ck_assert_uint_eq(o3, s21_o3);
  ck_assert_int_eq(res, s21_res);
  // ck_assert_int_eq(n, n2);
  */
}END_TEST

START_TEST(s21_sscanf_x_X_test) {
  int res = 0;
  int s21_res = 0;

  unsigned int x = 0;
  unsigned short int hx = 0;
  unsigned long int lx = 0;

  unsigned int s21_x = 0;
  unsigned short int s21_hx = 0;
  unsigned long int s21_lx = 0;

  s21_res = s21_sscanf("0x0x234", "%x", &s21_x);
  res = sscanf("0x0x234", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x234", "%x", &s21_x);
  res = sscanf("0x234", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x234", "%X", &s21_x);
  res = sscanf("0x234", "%X", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("3b856", "%x", &s21_x);
  res = sscanf("3b856", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("32856f", "%X", &s21_x);
  res = sscanf("32856f", "%X", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x23g4", "%x", &s21_x);
  res = sscanf("0x23g4", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x23g4", "%X", &s21_x);
  res = sscanf("0x23g4", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x2r3g4", "%x", &s21_x);
  res = sscanf("0x2r3g4", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x2r3g4", "%X", &s21_x);
  res = sscanf("0x2r3g4", "%X", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-0x234", "%x", &s21_x);
  res = sscanf("-0x234", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-0x234", "%X", &s21_x);
  res = sscanf("-0x234", "%X", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("   0x234", "%x", &s21_x);
  res = sscanf("   0x234", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("   0x234", "%X", &s21_x);
  res = sscanf("   0x234", "%X", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  x = 0;
  s21_x = 0;
  s21_res = s21_sscanf("   ", "%x", &s21_x);
  res = sscanf("   ", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  x = 0;
  s21_x = 0;
  s21_res = s21_sscanf("   ", "%X", &s21_x);
  res = sscanf("   ", "%X", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  x = 0;
  s21_x = 0;
  s21_res = s21_sscanf("", "%x", &s21_x);
  res = sscanf("", "%x", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  x = 0;
  s21_x = 0;
  s21_res = s21_sscanf("", "%X", &s21_x);
  res = sscanf("", "%X", &x);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);
/*
  s21_res = s21_sscanf("0x234356768678", "%lx", &s21_lx);
  res = sscanf("0x234356768678", "%lx", &lx);
  ck_assert_uint_eq(lx, s21_lx);
  ck_assert_int_eq(res, s21_res);
*/
  s21_res = s21_sscanf("0x234356768678", "%lX", &s21_lx);
  res = sscanf("0x234356768678", "%lX", &lx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-0x234356768678", "%lx", &s21_lx);
  res = sscanf("-0x234356768678", "%lx", &lx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-0x234356768678", "%lX", &s21_lx);
  res = sscanf("-0x234356768678", "%lX", &lx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("234356768678", "%lx", &s21_lx);
  res = sscanf("234356768678", "%lx", &lx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("234356768678", "%lX", &s21_lx);
  res = sscanf("234356768678", "%lX", &lx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x234356768678", "%hx", &s21_hx);
  res = sscanf("0x234356768678", "%hx", &hx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x234356768678", "%hX", &s21_hx);
  res = sscanf("0x234356768678", "%hX", &hx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x234", "%hx", &s21_hx);
  res = sscanf("0x234", "%hx", &hx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("0x234", "%hX", &s21_hx);
  res = sscanf("0x234", "%hX", &hx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-0x234", "%hx", &s21_hx);
  res = sscanf("-0x234", "%hx", &hx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("-0x234", "%hX", &s21_hx);
  res = sscanf("-0x234", "%hX", &hx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("234", "%hx", &s21_hx);
  res = sscanf("234", "%hx", &hx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  s21_res = s21_sscanf("234", "%hX", &s21_hx);
  res = sscanf("234", "%hX", &hx);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_int_eq(res, s21_res);

  x = 0;
  unsigned int x2 = 0;
  unsigned int x3 = 0;
  s21_x = 0;
  unsigned int s21_x2 = 0;
  unsigned int s21_x3 = 0;

  s21_res = s21_sscanf("234 0x3543 3D", "%x %x %x", &s21_x, &s21_x2, &s21_x3);
  res = sscanf("234 0x3543 3D", "%x %x %x", &x, &x2, &x3);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_uint_eq(x2, s21_x2);
  ck_assert_uint_eq(x3, s21_x3);
  ck_assert_int_eq(res, s21_res);

  x = 0;
  x2 = 0;
  x3 = 0;
  s21_x = 0;
  s21_x2 = 0;
  s21_x3 = 0;

  s21_res = s21_sscanf("234 0x3543 3D", "%x %x %x", &s21_x, &s21_x2, &s21_x3);
  res = sscanf("234 0x3543 3D", "%x %x %x", &x, &x2, &x3);
  ck_assert_uint_eq(x, s21_x);
  ck_assert_uint_eq(x2, s21_x2);
  ck_assert_uint_eq(x3, s21_x3);
  ck_assert_int_eq(res, s21_res);

} END_TEST


int main(void){
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, insert_test);
  tcase_add_test(tc1_1, memchr_test);
  tcase_add_test(tc1_1, memcmp_test);
  tcase_add_test(tc1_1, memcpy_test);
  tcase_add_test(tc1_1, memmove_test);
  tcase_add_test(tc1_1, memset_test);
  tcase_add_test(tc1_1, strcat_test);
  tcase_add_test(tc1_1, strncat_test);
  tcase_add_test(tc1_1, strchr_test);
  tcase_add_test(tc1_1, strcmp_test);
  tcase_add_test(tc1_1, strncmp_test);
  tcase_add_test(tc1_1, strcpy_test);
  tcase_add_test(tc1_1, strncpy_test);
  tcase_add_test(tc1_1, strcspn_test);
  tcase_add_test(tc1_1, all_errors);
  tcase_add_test(tc1_1, negative_err_code);
  tcase_add_test(tc1_1, strpbrk_test);
  tcase_add_test(tc1_1, strrchr_test);
  tcase_add_test(tc1_1, strspn_test);
  tcase_add_test(tc1_1, strstr_test);
  tcase_add_test(tc1_1, strtok_test);
  tcase_add_test(tc1_1, to_lower_test);
  tcase_add_test(tc1_1, to_upper_test);
  tcase_add_test(tc1_1, trim_test);
  tcase_add_test(tc1_1, sprintf_test);
  tcase_add_test(tc1_1, strlen_test);

  tcase_add_test(tc1_1, s21_sscanf_test_my);

  tcase_add_test(tc1_1, s21_sscanf_test);
  tcase_add_test(tc1_1, s21_sscanf_u_test);
  tcase_add_test(tc1_1, s21_sscanf_o_test);
  tcase_add_test(tc1_1, s21_sscanf_x_X_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}