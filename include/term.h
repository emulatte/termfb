#ifndef __TERM__
#define __TERM__

#include <termios.h>

typedef struct {
	struct termios previous;
	struct termios current;
} Term;

void term_uncook(Term *p_term);
void term_revert(Term *p_term);

#endif
