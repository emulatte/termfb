#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include "term.h"

void initterm(term **t) {
	*t = malloc(sizeof(term));
	term *te = *t;
	tcgetattr(STDIN_FILENO, &te->current);
	te->previous = te->current;

	te->curd = malloc(sizeof(char)*255); // future: set this to be system expected max
	updcurd(te, NULL);	
}

void term_uncook(term *p_term){

	struct termios *cur = &p_term->current;
	
	// Set flags
	cur->c_lflag &= ~(ICANON | ECHO | ISIG | IEXTEN);
	cur->c_oflag &= ~(OPOST);
	cur->c_iflag &= ~(ICRNL | IXON);

	cur->c_cc[VMIN] = 1;
	cur->c_cc[VTIME] = 0;
	
	tcsetattr(STDIN_FILENO, TCSANOW, cur);

	//printf("\x1b[?25l"); // hide cursor
	printf("\x1b[s"); // save cursor pos
	printf("\x1b[?47h"); // save screen
	printf("\x1b[?1049h"); // alt buff
				
	// Disable Buffering for stdio
	setbuf(stdout, NULL); 
}

void term_revert(term *p_term) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &p_term->previous);

	printf("\033[3J"); // Clear alt buff
	printf("\x1b[?1049l"); // return buff
	printf("\x1b[?47l"); // restore screen
	printf("\x1b[u"); // restore cursor position
	//printf("\x1b[?25h"); // restore cursor
}

void cursync(term *t) {
	printf("\033[%i;%iH", t->cury+1, t->curx+1);
}

void updcurd(term *t, char *dir) {
	if (dir == NULL) {
		getcwd(t->curd, sizeof(char)*255); // again, 255 should change to system max
	} else {
		t->curd = memcpy(t->curd, dir, strlen(dir));
	}
}
