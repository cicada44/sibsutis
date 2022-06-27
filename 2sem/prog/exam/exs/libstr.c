#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "listr.h"

uint64_t cnt_sym(char *s, char sym)
{
    uint64_t cnt = 0;
    for (uint64_t x = 0; *(s + x) != '\0'; x++)
    {
        if (*(s + x) == sym)
            cnt++;
    }
    return cnt;
}

int is_value_in_char_arr(char *s, char c)
{
    for (int x = 0; *(s + x) != '\0'; x++)
        if (*(s + x) == c)
            return 0;
    return 1;
}

int correct_IP_check(char *s)
{
    int cnt_c = 0;
    int c = 0, cnt = 0;
    char *syms = "1234567890.";

    int cnt_commas = cnt_sym(s, '.');
    if (cnt_commas != 3)
        return -1;

    int flag_correct = correct_suff(s, syms, strlen(s));
    if (flag_correct)
        return 0;

    for (int x = 0; *(s + x) != '\0'; x++)
    {
        cnt = 0;
        if (cnt_c != 3)
            for (; *(s + c) != '.'; c++)
            {
                cnt++;
            }
        else
        {
            for (; *(s + c) != '\0'; c++)
            {
                cnt++;
            }
        }
        if (cnt > 3)
        {
            flag_correct = 1;
            break;
        }
        if (cnt_commas == 3)
            break;
        cnt_c++;
        c++;
    }

    printf("correct - %d\n", flag_correct);
    return flag_correct;
}

int correct_suff(char *s, char *syms, unsigned int pre)
{
    int flag;
    for (int i = 0; *(syms + i) != '\0'; i++)
    {
        for (int x = 0; x < pre; x++)
        {
            flag = 1;
            if (*(s + x) == *(syms + i))
            {
                flag = 0;
                break;
            }
        }
        if (flag)
            return 1;
    }
    return 0;
}

char *str_insert(char *str_s, char *str_p, unsigned int pos, char *str_o)
{
    unsigned int len1 = strlen(str_s);
    unsigned int len2 = strlen(str_p);
    unsigned int len = len1 + len2;
    int c = 0, i = 0;
    while (c < len)
    {
        if (c == pos)
        {
            i = c;
            for (int x = 0; x < strlen(str_p); x++)
            {
                *(str_o + c) = *(str_p + x);
                c++;
            }
        }
        *(str_o + c) = *(str_s + i);
        c++;
        i++;
    }
    str_o[strlen(str_o)] = '\0';
    return str_o;
}

char *delete_str(char *s, char *s_del, char *buf)
{
    int c = 0;
    int i = 0;
    for (int x = 0; *(s + x) != '\0'; x++)
    {
        while (c < strlen(s_del))
        {
            if (*(s + x) != *(s_del + c))
                break;
            c++;
            x++;
        }
        *(buf + i) = *(s + x);
        i++;
    }
    return buf;
}

int str_to_uint(char *s)
{
    int len = strlen(s);
    int cnt = 0;
    unsigned int temp;
    for (int x = 0; x < len; x++)
    {
        temp = *(s + x) - '0';
        for (int i = 0; i < len - x - 1; i++)
            temp *= 10;
        cnt += temp;
    }
    return cnt;
}

char *uint_to_str(int t, char *buf)
{
    int temp = t, st;
    int r = 0;
    while (t > 0)
    {
        t /= 10;
        r++;
    }
    for (int x = 0; x < r; x++)
    {
        st = 1;
        for (int i = 0; i < r - x - 1; i++)
            st *= 10;
        *(buf + x) = temp / st + '0';
        temp %= st;
    }
    return buf;
}

char *strcncat(char *s1, char *s2, char *buf)
{
    int x;
    for (x = 0; *(s1 + x) != '\0'; x++)
        *(buf + x) = *(s1 + x);
    for (int i = 0; *(s2 + i) != '\0'; i++)
    {
        *(buf + x) = *(s2 + i);
        x++;
    }
    buf[strlen(buf)] = '\0';
    return buf;
}

int strcmp_r(char *s1, char *s2)
{
    int cmp;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 != len2)
    {
        if (len1 < len2)
            cmp = -1;
        else
            cmp = 1;
        return cmp;
    }
    int x = 0, i = 0;
    while ((*(s1 + x) && *(s2 + i)) != '\0')
    {
        if (*(s1 + x) < *(s2 + i))
            return -1;
        else if (*(s1 + x) > *(s2 + i))
            return 1;
        x++;
        i++;
    }
    return 0;
}

char *str_cp(char *s1, char *buf)
{
    for (int x = 0; *(s1 + x) != '\0'; x++)
        *(buf + x) = *(s1 + x);
    return buf;
}

char *snake_to_camel(char *s1, char *buf)
{
    int i = 0;
    for (int x = 0; *(s1 + x) != '\0'; x++)
    {
        if (*(s1 + x) == '_')
        {
            ++x;
            *(buf + i) = toupper(*(s1 + x));
            i++;
            continue;
        }
        *(buf + i) = *(s1 + x);
        i++;
    }
    return buf;
}

char *camel_to_snake(char *s1, char *buf)
{
    int i = 0;
    for (int x = 0; *(s1 + x) != '\0'; x++)
    {
        *(buf + i) = *(s1 + x);
        if (isupper(*(s1 + x)))
        {
            *(buf + i) = '_';
            *(buf + i + 1) = tolower(*(s1 + x));
            i++;
        }
        i++;
    }
    return buf;
}

void str_tok(char *s, char del, char **arr)
{
    int i = 0, j = 0;
    for (int x = 0; *(s + x) != '\0'; x++)
    {
        if (*(s + x) == del)
        {
            i++;
            j = 0;
            continue;
        }
        arr[i][j] = *(s + x);
        j++;
    }
}

int str_locate_locket_sym(char *src, char *symb, unsigned int c)
{
    for (int x = 0; x < c; x++)
    {
        for (int i = 0; *(symb + i) != '\0'; i++)
        {
            if (*(symb + i) == *(src + x))
                return 1;
        }
    }
    return 0;
}

char *str_str(char *src, char *find_s)
{
    int len = strlen(find_s);
    int i = 0, j = 0;
    for (int x = 0; *(src + x) != '\0'; x++)
    {
        j = x;
        i = 0;
        while ((*(src + j) == *(find_s + i)) != '\0')
        {
            if (len - 1 == i)
                return src + x;
            i++;
            j++;
        }
    }
    return NULL;
}