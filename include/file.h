#ifndef __FBFILE__
#define __FBFILE__

#include <dirent.h>

typedef int (*sortfunc)(const void *, const void *);

int getntype(char *path);
int openapp(char *path);
int alphadirsort(const void *, const void *);

int absscandir(char *abspath, char ***nodes, sortfunc);

#endif
