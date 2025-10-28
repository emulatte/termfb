#ifndef __DISPLAY__
#define __DISPLAY__

typedef struct {
	int w;
	int h;
	int o;
	int buffc;
	char **buff;
} scr;

void lsdir(scr *s, char *dir);

void initscr(scr **s);
void updim(scr *s);
void inscr(scr *s, char *in, int inc);
void mvscr(scr *s, int offset); 
void clscr(scr *s);
void shscr(scr *s);


#endif
