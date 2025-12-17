#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include "file.h"
#include "input.h"
#include "fb.h"
#include "term.h"
#include "display.h"

char handleinput(fb *f, char in) {
	updim(f->s);

	switch(in) {
		case MV_UP:
			handlemove(f, MV_UP);
			break;
		case MV_DOWN:
			handlemove(f, MV_DOWN);
			break;
		case MV_LEFT:
			handlemove(f, MV_LEFT);
			break;
		case MV_RIGHT:
			handlesel(f);
			break;
		case SL_ENTER:
			handlesel(f);
		case QUIT_TFB:
			break;
	}

	return in;
}

void handlesel(fb *f) {

	if (getntype(f->cursel) == S_IFDIR) { 
		if (! chgdir(f, f->cursel)) {
			return;
		}
	} else {
		openapp(f->cursel);
	}
}

void handlemove(fb *f, char direc) {
	switch(direc) {
		case MV_UP:
			if (f->t->cury -1 == -1 && f->s->o > 0) {
				mvscr(f->s, -1);
			}

			if (f->t->cury -1 >= 0) {
				f->t->cury-=1;
			}
			break;

		case MV_DOWN:
			if (f->t->cury + 2 == f->s->h && f->s->o < f->s->buffc - f->s->h) {
				mvscr(f->s, 1);
			}

			if (f->t->cury + 1 < f->s->h - 1 && f->t->cury + 1 < f->s->buffc) { 
				f->t->cury+=1;
			}
			break;

		case MV_LEFT:
			chgdir(f, "..");
			break;
	}
} 

char getinput() {
	char in = getchar();

	return in;
}
