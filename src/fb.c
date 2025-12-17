#include <dirent.h>
#include <limits.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "term.h"
#include "display.h"
#include "fb.h"
#include "file.h"

int initfb(fb **f, char *path) {
	*f = malloc(sizeof(fb));
	fb *ft = *f;

	initterm(&(ft->t));
	term_uncook(ft->t);

	initscr(&(ft->s));

	ft->wrkdir = malloc(PATH_MAX);
	ft->curdir = malloc(PATH_MAX);
	ft->cursel = malloc(PATH_MAX);

	getcwd(ft->wrkdir, PATH_MAX);

	if (path) {
		realpath(path, ft->curdir);	
	}
	else {
		getcwd(ft->curdir, PATH_MAX);
	}

	upddbuff(ft, ft->curdir);

	if ((*f)->dirbuffc <= 0) {
		return 0;
	}

	updcursel(ft);

	return 1;
}

void upddbuff(fb *f, char *path) {
	char **dirs;

	int dcount = absscandir(path, &dirs, alphadirsort);
	f->dirbuffc = dcount - 1; // we're ommiting "."
	f->dirbuff = realloc(f->dirbuff, f->dirbuffc * sizeof(char*));

	for (int i = 0, i2 = 0; i2 < dcount; i++, i2++) {
		if (strcmp(basename(dirs[i2]), ".") == 0) {
			i--;
			continue;
		}

		f->dirbuff[i] = dirs[i2];
	}

	f->t->cury = 0;
	f->s->o = 0;
}

void updcurdir(fb *f, char *path) {
	memcpy(f->curdir, path, strlen(path)+1);
}

void updcursel(fb *f) {
	strcpy(f->cursel, f->dirbuff[(f->t->cury + f->s->o)]);
}

void updwrkdir(fb *f, char *path) {
	memcpy(f->wrkdir, path, strlen(path)+1);
}

int chgdir(fb *f, char *path) {
	if (!opendir(path)) {
		return 0;
	}

	if (path[strlen(path) - 1] == '.' && path[strlen(path) - 2] == '.') {
		updcurdir(f, dirname(f->curdir));
	} else if (path[strlen(path) - 1] == '.'){
		// ignore current dir (ideally these won't be visible :)
	} else {
		updcurdir(f, path);	 
	}
		
	upddbuff(f, f->curdir);

	return 1;
}

void lscurdir(fb *f) {	
	char *istr;
	for (int i = 0; i < f->dirbuffc; i++) {
		if (getntype(f->dirbuff[i]) == S_IFDIR) {
			colorstr(basename(f->dirbuff[i]), &istr, S_IFDIR);
		} else {
			istr = basename(f->dirbuff[i]);
		}
		inscr(f->s, istr);
	}
}
