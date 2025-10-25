#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "term.h"

void term_uncook(Term *p_term){

	struct termios *cur = &p_term->current;
	
	// Set flags
	cur->c_lflag &= ~(ICANON | ECHO | ISIG | IEXTEN);
	cur->c_oflag &= ~(OPOST);
	cur->c_iflag &= ~(ICRNL | IXON);

	cur->c_cc[VMIN] = 1;
	cur->c_cc[VTIME] = 0;
	
	tcsetattr(STDIN_FILENO, TCSANOW, cur);

	printf("\x1b[?25l"); // hide cursor
	printf("\x1b[s"); // save cursor pos
	printf("\x1b[?47h"); // save screen
	printf("\x1b[?1049h"); // alt buff
}

void term_revert(Term *p_term) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &p_term->previous);

	printf("\x1b[?1049l"); // return buff
	printf("\x1b[?47l"); // restore screen
	printf("\x1b[u"); // restore cursor position
	printf("\x1b[?25h"); // restore cursor
}
