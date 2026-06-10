#ifndef LIBK_H
#define LIBK_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

char *strcpy(char *dest, const char *src);
int strlen(const char *str);
void *memset(void *s, int c, int n);
void *memcpy(void *dest, const void *src, int n);
int strcmp(const char *s1, const char *s2);
void itoa(int num, char *str, int base);
void printf(const char *fmt, ...);

#endif
