#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include "display.h"
#include "term.h"

void lsdir(term *t, scr *s, char *dir) {
	struct dirent **dirs;
	int result = scandir(dir, &dirs, NULL, alphasort);
	for (int i = 0; i < result; i++) {
		inscr(s, dirs[i]->d_name);
	}
}

void updftr(term *t, scr *s, char *fstr) {
	int sx = s->w;
	int sy = s->h;

	int si = t->cury + s->o; // y + offset
	int fslen = strlen(fstr);
	printf("\033[%i;%iH%s", sy, sx - fslen + 1, fstr);
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

void stripn(char *in, char **out) {
	int inc = strlen(in) + 1;
	*out = malloc(inc);
	*out = memcpy(*out, in, inc);
	for (int i = 0; (*out)[i] != '\0'; i++) {
		if ((*out)[i] == '\n') {
			(*out)[i] = '\0';
		}
	}
}

void shscr(term *t, scr *s, char *fstr) {
	printf("\033[3J\033[H"); // Clear screen, set cursor 0,0
	for (int i = s->o; i < s->buffc && i - s->o < s->h ; i++) {
		if (i - s->o == s->h - 2) {
			// strip new line if last in term screen
			char *stpd;
			stripn(s->buff[i], &stpd);
			printf(stpd);
			free(stpd);
		}else {
			printf(s->buff[i]);
		}
	}
	
	updftr(t, s, fstr);
	cursync(t);
}

void clscr(scr *s) {
	for (int i = 0; i < s->buffc; i++) {
		free(s->buff[i]);
	}

	s->buffc = 0;
}

void mvscr(scr *s, int offset) {
	if (s->o + offset >= 0) {
		s->o += offset;
	}
}

void inscr(scr *s, char *in) {
	int inc = strlen(in);
	if (s->buffc == 0) {
		s->buff[0] = malloc(inc + 3);
		
		s->buff[0][inc] = '\r';
		s->buff[0][inc + 1] = '\n';
		s->buff[0][inc + 2] = '\0';
	} else {
		s->buff = realloc(s->buff, sizeof(char*) * (s->buffc + 1));
		s->buff[s->buffc] = malloc(inc + 3);

		s->buff[s->buffc][inc] = '\r';
		s->buff[s->buffc][inc + 1] = '\n';
		s->buff[s->buffc][inc + 2] = '\0';
	}

	memcpy(s->buff[s->buffc], in, inc);	
	s->buffc += 1;
}
