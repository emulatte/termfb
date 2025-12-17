#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <libgen.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include "file.h"

int getntype(char *path) {
	struct stat st = {0};
	stat(path, &st);
	
	return st.st_mode & S_IFMT;
}

int alphadirsort(const void *a, const void *b) {
	const char *ap = *(const char * const *)a;
	const char *bp = *(const char * const *)b;

	// For pure alphebetical sorting, we only need base name. To determine
	// if a node is a directory, absolute paths work better in a design
	// that keeps the working directory static. This is the reason we are not
	// using scandir and its expectation of dirent argument'd sort functions.

	char afull[PATH_MAX];
	char bfull[PATH_MAX];

	char abase[PATH_MAX];
	char bbase[PATH_MAX];

	strcpy(afull, ap);
	strcpy(bfull, bp);

	strcpy (abase, basename(afull));
	strcpy (bbase, basename(bfull));

	// Sort based on dir -> dir alpha -> all other alpha
	if (getntype(afull) == S_IFDIR && !(getntype(bfull) == S_IFDIR))  {
		return 0;
	} else if (getntype(bfull) == S_IFDIR && !(getntype(afull) == S_IFDIR)) {
		return 1;
	} else if (getntype(afull) == S_IFDIR && getntype(bfull) == S_IFDIR) {
		return strcmp(abase, bbase);	
	}

	return strcmp(abase, bbase);	
}

int absscandir(char *abspath, char ***nodes, sortfunc sfunc) {
	DIR *f = opendir(abspath);
	struct dirent *de;
	int dcnt = 0;	

	while (f && (de = readdir(f))) {
		dcnt += 1;
	}

	if (dcnt <= 0) {
		// This means not even . or ..
		return dcnt;
	}

	rewinddir(f);
	*nodes = malloc(sizeof(char *) * dcnt); 
	char absp[PATH_MAX];
	for (int i = 0; (de = readdir(f)) != NULL; i++) {
		strcpy(absp, abspath);
		if (! (strlen(abspath) == 1 && abspath[0] == '/')) {
			strcpy(absp + strlen(absp), "/");
		}

		strcpy(absp + strlen(absp), de->d_name);

		(*nodes)[i] = malloc(strlen(absp) + 1);
		strcpy((*nodes)[i], absp);
	}

	qsort(*nodes, dcnt, sizeof(char*), alphadirsort);
	return dcnt;
}

int openapp(char *path) {
	int pid = fork();

	if (pid == 0) {
	
		// Set new session and prevent apps from latching onto existing stdin,out,err.
		// Currently terminal based apps not properly supported...
		// Looking into least awkward way to handle this.
		
        setsid();
        fclose(stdin);
        fclose(stdout);
        fclose(stderr);
		execlp("xdg-open", "xdg-open", path, NULL);
	}
}
