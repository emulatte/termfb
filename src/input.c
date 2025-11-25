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
			handlemove(f, MV_RIGHT);
			break;
		case SL_ENTER:
			handlesel(f);
		case QUIT_TFB:
			break;
	}

	return in;
}

void handlesel(fb *f) {
	char abs[PATH_MAX];
	strcpy(abs, f->curdir);
	strcpy(abs+strlen(abs),"/");
	strcpy(abs+strlen(abs), f->cursel);

	if (getntype(abs) == S_IFDIR) { 
		chgdir(f, f->cursel);
	} else {
		openapp(abs);
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

		case MV_RIGHT:
			chgdir(f, f->cursel);
	}
} 

char getinput() {
	char in = getchar();

	return in;
}
