#include "../include/file.h"
#include "../include/kernel.h"
#include "../include/module.h"
#include "../include/libc.h"

int libc;

void *(*malloc)(size_t size);
void (*free)(void *ptr);
void *(*calloc)(size_t num, size_t size);
void *(*realloc)(void *ptr, size_t size);
void *(*memalign)(size_t boundary, size_t size);
void *(*memset)(void *destination, int value, size_t num);
void *(*memcpy)(void *destination, const void *source, size_t num);
int (*memcmp)(const void *s1, const void *s2, size_t n);
void *(*memmove)(void *dst, const void *src, size_t len);
errno_t (*memmove_s)(void *dest, rsize_t destsz, const void *src, rsize_t count);
char *(*strcpy)(char *destination, const char *source);
char *(*strncpy)(char *destination, const char *source, size_t num);
errno_t *(*strncpy_s)(char *restrict dest, rsize_t destsz, const char *restrict src, rsize_t count);
char *(*strcat)(char *dest, const char *src);
char *(*strncat)(char *dest, const char *src, size_t n);
size_t (*strlen)(const char *s);
int (*strcmp)(const char *s1, const char *s2);
int (*strncmp)(const char *s1, const char *s2, size_t n);
int (*sprintf)(char *str, const char *format, ...);
int (*snprintf)(char *str, size_t size, const char *format, ...);
int (*snprintf_s)(char *restrict buffer, rsize_t bufsz, const char *restrict format, ...);
int (*sscanf)(const char *str, const char *format, ...);
int (*strtol)(const char* s1, char** s2, int base);
char *(*strtok)(char *str, const char *delimiters);
char *(*strchr)(const char *s, int c);
char *(*strrchr)(const char *s, int c);
char *(*strstr)(char *str1, char *str2);
char *(*strdup)(const char *s);
char *(*strtok)(char *str, const char *sep);
char *(*index)(const char *s, int c);
char *(*rindex)(const char *s, int c);
int (*isdigit)(int c);
int (*atoi)(const char *s);
double (*atof)(const char *s);
size_t (*strlcpy)(char *dst, const char *src, size_t size);
char *(*strerror)(int errnum);
void *(*_Getpctype)();
unsigned long (*_Stoul)(const char *, char **, int);
void (*bcopy)(const void *s1, void *s2, size_t n);
double (*ceil)(double x);

void (*srand)(unsigned int seed);
int (*rand)(void);

char *(*asctime)(const struct tm *tm);
char *(*asctime_r)(const struct tm *tm, char *buf);
char *(*ctime)(const time_t *timep);
char *(*ctime_r)(const time_t *timep, char *buf);
time_t (*time)(time_t *tloc);
struct tm *(*gmtime)(const time_t *timep);
struct tm *(*gmtime_s)(const time_t *timep, struct tm *result);
struct tm *(*localtime)(const time_t *timep);
struct tm *(*localtime_r)(const time_t *timep, struct tm *result);
time_t (*mktime)(struct tm *tm);

DIR *(*opendir)(const char *filename);
struct dirent *(*readdir)(DIR *dirp);
int (*readdir_r)(DIR *dirp, struct dirent *entry, struct dirent **result);
long (*telldir)(const DIR *dirp);
void (*seekdir)(DIR *dirp, long loc);
void (*rewinddir)(DIR *dirp);
int (*closedir)(DIR *dirp);
int (*dirfd)(DIR *dirp);
char *(*getprogname)();

FILE *(*fopen)(const char *filename, const char *mode);
size_t (*fread)(void *ptr, size_t size, size_t count, FILE *stream);
size_t (*fwrite)(const void *ptr, size_t size, size_t count, FILE *stream);
int (*fseek)(FILE *stream, long int offset, int origin);
long int (*ftell)(FILE *stream);
int (*fclose)(FILE *stream);
int (*fprintf)(FILE *stream, const char *format, ...);

int memset_s(void *s, rsize_t smax, int c, rsize_t n) {
  BOOL violation = (s == NULL) || (smax > RSIZE_MAX) || (n > RSIZE_MAX) || (n > smax);
  if (violation) {
    if ((s != NULL) && !(smax > RSIZE_MAX)) {
      for (rsize_t i = 0; i < smax; ++i) {
        ((volatile unsigned char *)s)[i] = c;
      }
    }
    return 1;
  } else {
    for (rsize_t i = 0; i < n; ++i) {
      ((volatile unsigned char *)s)[i] = c;
    }
    return 0;
  }
}

void initLibc(void) {
  if (libc) return;

  libc = sceKernelLoadStartModule("libSceLibcInternal.sprx", 0, 0, 0, NULL, NULL);

  HOOKFUNCTION(libc, malloc);
  HOOKFUNCTION(libc, free);
  HOOKFUNCTION(libc, calloc);
  HOOKFUNCTION(libc, realloc);
  HOOKFUNCTION(libc, memalign);
  HOOKFUNCTION(libc, memset);
  HOOKFUNCTION(libc, memcpy);
  HOOKFUNCTION(libc, memcmp);
  HOOKFUNCTION(libc, memmove);
  HOOKFUNCTION(libc, memmove_s);
  HOOKFUNCTION(libc, strcpy);
  HOOKFUNCTION(libc, strncpy);
  HOOKFUNCTION(libc, strncpy_s);
  HOOKFUNCTION(libc, strcat);
  HOOKFUNCTION(libc, strncat);
  HOOKFUNCTION(libc, strlen);
  HOOKFUNCTION(libc, strcmp);
  HOOKFUNCTION(libc, strncmp);
  HOOKFUNCTION(libc, sprintf);
  HOOKFUNCTION(libc, snprintf);
  HOOKFUNCTION(libc, snprintf_s);
  HOOKFUNCTION(libc, sscanf);
  HOOKFUNCTION(libc, strtol);
  HOOKFUNCTION(libc, strtok);
  HOOKFUNCTION(libc, strchr);
  HOOKFUNCTION(libc, strrchr);
  HOOKFUNCTION(libc, strstr);
  HOOKFUNCTION(libc, strdup);
  HOOKFUNCTION(libc, strtok);
  HOOKFUNCTION(libc, index);
  HOOKFUNCTION(libc, rindex);
  HOOKFUNCTION(libc, isdigit);
  HOOKFUNCTION(libc, atoi);
  HOOKFUNCTION(libc, atof);
  HOOKFUNCTION(libc, strlcpy);
  HOOKFUNCTION(libc, strerror);
  HOOKFUNCTION(libc, _Getpctype);
  HOOKFUNCTION(libc, _Stoul);
  HOOKFUNCTION(libc, bcopy);
  HOOKFUNCTION(libc, ceil);

  HOOKFUNCTION(libc, srand);
  HOOKFUNCTION(libc, rand);

  HOOKFUNCTION(libc, asctime);
  HOOKFUNCTION(libc, asctime_r);
  HOOKFUNCTION(libc, ctime);
  HOOKFUNCTION(libc, ctime_r);
  HOOKFUNCTION(libc, time);
  HOOKFUNCTION(libc, gmtime);
  HOOKFUNCTION(libc, gmtime_s);
  HOOKFUNCTION(libc, localtime);
  HOOKFUNCTION(libc, localtime_r);
  HOOKFUNCTION(libc, mktime);

  HOOKFUNCTION(libc, opendir);
  HOOKFUNCTION(libc, readdir);
  HOOKFUNCTION(libc, readdir_r);
  HOOKFUNCTION(libc, telldir);
  HOOKFUNCTION(libc, seekdir);
  HOOKFUNCTION(libc, rewinddir);
  HOOKFUNCTION(libc, closedir);
  HOOKFUNCTION(libc, dirfd);

  HOOKFUNCTION(libc, getprogname);

  HOOKFUNCTION(libc, fopen);
  HOOKFUNCTION(libc, fread);
  HOOKFUNCTION(libc, fwrite);
  HOOKFUNCTION(libc, fseek);
  HOOKFUNCTION(libc, ftell);
  HOOKFUNCTION(libc, fclose);
  HOOKFUNCTION(libc, fprintf);
}
