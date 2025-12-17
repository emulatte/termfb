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
	int result;

	if (argc > 1) {
		result = initfb(&f, argv[1]);
	
	} else {
		result = initfb(&f, NULL);
	}

	if (!result) {
		printf("Failed to initialize termfb!\n");
		getchar();
		term_revert(f->t);
		return 1;
	}

	lscurdir(f);
	shscr(f->t, f->s, f->curdir);

	char c = ' ';
	while (c = handleinput(f, getinput())) {
		if (c == QUIT_TFB) {
			break;
		}

		clscr(f->s);

		lscurdir(f);
		updcursel(f);
		shscr(f->t, f->s, f->curdir);

	}

	term_revert(f->t);
	return 0;
}
