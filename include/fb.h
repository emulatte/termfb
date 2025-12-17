#ifndef __FBROWSE__
#define __FBROWSE__

#include "term.h"
#include "display.h"

typedef struct {
	term *t;
	scr *s;
	char *cursel;
	char *curdir;
	char *wrkdir;
	int dirbuffc;
	char **dirbuff;
} fb;

int initfb(fb **, char *);

void upddbuff(fb *, char *);
void updcurdir(fb *, char *);
void updcursel(fb *);
void updwrkdir(fb *, char *);

void lscurdir(fb *);

int chgdir(fb *, char *);

#endif
