#include <stdio.h>
#include "input.h"
#include "term.h"
#include "display.h"

char handleinput(term *t, scr *s, char in) {
	switch(in) {
		case MV_UP:
			handlemove(t, s, MV_UP);
			break;
		case MV_DOWN:
			handlemove(t, s, MV_DOWN);
			break;
		case MV_LEFT:
			handlemove(t, s, MV_LEFT);
			break;
		case MV_RIGHT:
			handlemove(t, s, MV_RIGHT);
			break;
		case QUIT_TFB:
			break;
	}

	shscr(t, s);
	return in;
}

void handlemove(term *t, scr *s, char direc) {
	switch(direc) {
		case MV_UP:
			if (t->cury -1 == -1 && s->o > 0) {
				mvscr(s, -1);
			}

			if (t->cury -1 >= 0) {
				t->cury-=1;
			}
			break;

		case MV_DOWN:
			if (t->cury + 2 == s->h && s->o < s->buffc - s->h) {
				mvscr(s, 1);
			}

			if (t->cury + 1 < s->h - 1 && t->cury + 1 < s->buffc) { 
				t->cury+=1;
			}
			break;

		case MV_LEFT:
			break;

		case MV_RIGHT:
			break;
	}
} 

char getinput() {
	char in = getchar();

	return in;
}
