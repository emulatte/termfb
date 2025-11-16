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

	upddbuff(f, "/home/tristan/Test");

	char c = ' ';
	while (c = handleinput(f->t, f->s, getinput())) {
		if (c == QUIT_TFB) {
			break;
		}
	}
	
	term_revert(f->t);
	return 0;
}
