#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "fb.h"
#include "file.h"
#include "input.h"
#include "term.h"
#include "display.h"

int main(int argc, char *argv[]) {

	fb *f;

	if (argc > 1) {
		initfb(&f, argv[1]);
	
	} else {
		initfb(&f, NULL);
	}


	lsdir(f, f->curdir);
	shscr(f->t, f->s, f->curdir);

	char c = ' ';
	while (c = handleinput(f, getinput())) {
		if (c == QUIT_TFB) {
			break;
		}

		clscr(f->s);

		lsdir(f, f->curdir);
		updcursel(f);
		shscr(f->t, f->s, f->curdir);

	}

	term_revert(f->t);
	return 0;
}
