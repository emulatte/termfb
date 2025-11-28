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
	struct dirent **dirs;

	f->dirbuffc = scandir(path, &dirs, NULL, alphasort) - 1; // -1 to omit '.'
	f->dirbuff = realloc(f->dirbuff, f->dirbuffc * sizeof(char*));

	for (int i = 0; i < f->dirbuffc; i++) {
		f->dirbuff[i] = dirs[i+1]->d_name; // i+1 to omit '.'
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
	if (path[0] == '/') {
		updcurdir(f, path);
	} else if (path[0] == '.' && path[1] == '.') {
		updcurdir(f, dirname(f->curdir));
	} else if (path[0] == '.' && strlen(path) == 1){
	} else {
		if (strlen(f->curdir) != 1) {
			strcpy(f->curdir + strlen(f->curdir), "/");
		}
		strcpy(f->curdir + strlen(f->curdir), path);
	 }
		
	upddbuff(f, f->curdir);
}

void lsdir(fb *f, char *dir) {
	struct dirent **nodes;
	int color = 0;
	char *istr;
	
	char *abspth = malloc(PATH_MAX + 1);

	if (dir[0] == '/') {
		color = 1;
	}

	int result = scandir(dir, &nodes, NULL, alphasort);
	for (int i = 1; i < result; i++) { // i = 1, skip '.'
		if (color) {
			strcpy(abspth, dir);
			strcpy(abspth + strlen(abspth), "/");
			strcpy(abspth + strlen(abspth), nodes[i]->d_name);
		}

		if (color && getntype(abspth) == S_IFDIR) {
			colorstr(nodes[i]->d_name, &istr, S_IFDIR);
		} else {
			istr = nodes[i]->d_name;
		}

		inscr(f->s, istr);
	}
}
