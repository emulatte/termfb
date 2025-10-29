#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include "display.h"
#include "term.h"

void lsdir(term *t, scr *s, char *dir) {
	DIR *ldir = opendir(dir);

	struct dirent *curdir;
	while ((curdir = readdir(ldir)) != NULL) {
		inscr(s, curdir->d_name);
		inscr(s, "\n\r");
	}

	shscr(t, s);
}

void initscr(scr **s) {
	*s = malloc(sizeof (scr));
	(*s)->buffc = 0;
	(*s)->buff = malloc(sizeof (char *));
	updim(*s);	
}

void updim(scr *s) {
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	s->w = w.ws_col;
	s->h = w.ws_row;
}

int countnl(char *ca) {
	int i = 0;
	int nlc = 0;
	while (ca[i] != '\0') {
		if (ca[i] == '\n') {
			nlc += 1;
		}
		i++;
	}

	return nlc;
}

void shscr(term *t, scr *s) {
	int nlc = 0;
	
	printf("\033[3J\033[H");
	for (int i = s->o; i < s->buffc && nlc < s->h; i++) {
		printf(s->buff[i]);
		nlc += countnl(s->buff[i]);
	}

	cursync(t);	
}

void mvscr(scr *s, int offset) {
	if (s->o + offset >= 0) {
		s->o += offset;
	}
}

void inscr(scr *s, char *in) {
	int inc = strlen(in);
	if (s->buffc == 0) {
		s->buff[0] = malloc(sizeof(inc) + 1);
		s->buff[0][inc] = '\0';
	} else {
		s->buff = realloc(s->buff, sizeof(char*) * (s->buffc + 1));
		s->buff[s->buffc] = malloc(sizeof(inc + 1));
		s->buff[s->buffc][inc] = '\0';
	}

	memcpy(s->buff[s->buffc], in, inc);	
	s->buffc += 1;
}
