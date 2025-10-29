#ifndef __DISPLAY__
#define __DISPLAY__

#include "term.h"

typedef struct {
	int w;
	int h;
	int o;
	int buffc;
	char **buff;
} scr;

void lsdir(term *t, scr *s, char *dir);

void initscr(scr **s);
void updim(scr *s);
void inscr(scr *s, char *in);
void mvscr(scr *s, int offset); 
void clscr(scr *s);
void shscr(term *t, scr *s);

int countnl(char *ca);

#endif
