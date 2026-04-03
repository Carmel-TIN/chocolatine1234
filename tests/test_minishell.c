/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** description
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

Test(my_strdup, duplicate_simple_string)
{
    char *src = "hello";
    char *dup = my_strdup(src);

    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, src);
    free(dup);
}

Test(my_strdup, duplicated_string_is_independent)
{
    char *src = "hello";
    char *dup = my_strdup(src);

    dup[0] = 'H';
    cr_assert_str_eq(src, "hello");
    cr_assert_str_eq(dup, "Hello");
    free(dup);
}

Test(my_strdup, empty_string)
{
    char *dup = my_strdup("");

    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "");
    free(dup);
}

Test(my_getnbr, negative_number)
{
    cr_assert_eq(my_getnbr("-100"), -100);
    cr_assert_eq(my_getnbr("-123456789"), -123456789);
    cr_assert_eq(my_getnbr("-987654321"), -987654321);
    cr_assert_eq(my_getnbr("-34567"), -34567);
    cr_assert_eq(my_getnbr("-123456"), -123456);
    cr_assert_eq(my_getnbr("-1"), -1);
}

Test(my_getnbr, positive_number)
{
    cr_assert_eq(my_getnbr("100"), 100);
    cr_assert_eq(my_getnbr("123456789"), 123456789);
    cr_assert_eq(my_getnbr("987654321"), 987654321);
    cr_assert_eq(my_getnbr("34567"), 34567);
    cr_assert_eq(my_getnbr("123456"), 123456);
    cr_assert_eq(my_getnbr("1"), 1);
}
