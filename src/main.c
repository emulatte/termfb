#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "input.h"
#include "term.h"
#include "display.h"

int main(int argc, char *argv[]) {

	term *t;
	initterm(&t);

	term_uncook(t);

	scr *s;
	initscr(&s);

	lsdir(t, s, "/home/tristan/.config/");

	char c = ' ';
	while (c = handleinput(t, s, getinput())) {
		if (c == QUIT_TFB) {
			break;
		}
	}
	
	term_revert(t);

	return 0;
}
