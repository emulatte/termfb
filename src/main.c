#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "fb.h"
#include "input.h"
#include "term.h"
#include "display.h"

int main(int argc, char *argv[]) {

	fb *f;
	initfb(&f);
	
	lsdir(f->t, f->s, f->curdir);
	shscr(f->t, f->s, f->curdir);

	char c = ' ';
	while (c = handleinput(f->t, f->s, getinput())) {
		if (c == QUIT_TFB) {
			break;
		}

		shscr(f->t, f->s, f->curdir);
	}

	term_revert(f->t);
	return 0;
}
