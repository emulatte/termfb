#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "term.h"
#include "display.h"

int main(int argc, char *argv[]) {
	
	Term t = {0};
	tcgetattr(STDIN_FILENO, &t.current);
	t.previous = t.current;

	term_uncook(&t);
	
	scr *s;
	initscr(&s);

	lsdir(s, ".");
	getchar();

	term_revert(&t);
	return 0;
}
