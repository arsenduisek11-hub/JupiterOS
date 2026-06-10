#include "libk.h"
#include <stdarg.h>

char *strcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return dest;
}

int strlen(const char *str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

void *memset(void *s, int c, int n) {
    unsigned char *p = (unsigned char *)s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

void *memcpy(void *dest, const void *src, int n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

void itoa(int num, char *str, int base) {
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    
    int i = 0;
    int is_neg = num < 0;
    if (is_neg) num = -num;
    
    while (num > 0) {
        int digit = num % base;
        str[i++] = digit < 10 ? ('0' + digit) : ('A' + digit - 10);
        num /= base;
    }
    
    if (is_neg) str[i++] = '-';
    str[i] = '\0';
    
    for (int j = 0; j < i / 2; j++) {
        char tmp = str[j];
        str[j] = str[i - 1 - j];
        str[i - 1 - j] = tmp;
    }
}

extern void putchar(char c);

void printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1)) {
            fmt++;
            switch (*fmt) {
                case 'd': {
                    int num = va_arg(args, int);
                    char buf[32];
                    itoa(num, buf, 10);
                    for (int i = 0; buf[i]; i++) putchar(buf[i]);
                    break;
                }
                case 'x': {
                    int num = va_arg(args, int);
                    char buf[32];
                    itoa(num, buf, 16);
                    for (int i = 0; buf[i]; i++) putchar(buf[i]);
                    break;
                }
                case 's': {
                    const char *str = va_arg(args, const char *);
                    while (*str) putchar(*str++);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    putchar(c);
                    break;
                }
                default:
                    putchar('%');
                    putchar(*fmt);
            }
        } else {
            putchar(*fmt);
        }
        fmt++;
    }
    
    va_end(args);
}
