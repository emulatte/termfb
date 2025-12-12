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

void initfb(fb **f, char *path) {
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
	updcursel(ft);
}

void upddbuff(fb *f, char *path) {
	char **dirs;

	f->dirbuffc = absscandir(path, &dirs, alphadirsort) - 1; // -1 to omit '.'
	f->dirbuff = realloc(f->dirbuff, f->dirbuffc * sizeof(char*));

	for (int i = 0; i < f->dirbuffc; i++) {
		f->dirbuff[i] = dirs[i+1]; // i+1 to omit '.'
	}

	f->t->cury = 0;
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

void chgdir(fb *f, char *path) {
	if (path[strlen(path) - 1] == '.' && path[strlen(path) - 2] == '.') {
		updcurdir(f, dirname(f->curdir));
	} else if (path[strlen(path) - 1] == '.'){
		// ignore current dir (ideally these won't be visible :)
	} else {
		updcurdir(f, path);	 
	}
		
	upddbuff(f, f->curdir);
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

