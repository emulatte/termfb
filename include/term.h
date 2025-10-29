#ifndef __TERM__
#define __TERM__

#include <termios.h>

typedef struct {
	struct termios previous;
	struct termios current;
	int curx;
	int cury;
} term;

void term_uncook(term *p_term);
void term_revert(term *p_term);

void cursync(term *t);

#endif
