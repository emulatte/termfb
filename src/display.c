#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include "display.h"

void lsdir(scr *s, char *dir) {
	DIR *ldir = opendir(dir);

	struct dirent *curdir;
	while ((curdir = readdir(ldir)) != NULL) {
		inscr(s, curdir->d_name, strlen(curdir->d_name));
		inscr(s, "\n\r", strlen("\n\r"));
	}

	shscr(s);
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

void shscr(scr *s) {
	printf("\033[H");	
	for (int i = 0; i < s->buffc; i++) {
		printf(s->buff[i]);
	}
	
}

void inscr(scr *s, char *in, int inc) {
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


