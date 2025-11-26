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

void updftr(term *t, scr *s, char *fstr);

void initscr(scr **s);
void updim(scr *s);
void inscr(scr *s, char *in);
void mvscr(scr *s, int offset); 
void clscr(scr *s);
void shscr(term *t, scr *s, char *fstr);

int countnl(char *ca);
void stripn(char *in, char **out);

#endif
