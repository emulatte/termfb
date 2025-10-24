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
}

void term_revert(Term *p_term) {
	tcsetattr(STDIN_FILENO, TCSANOW, &p_term->previous);
}
