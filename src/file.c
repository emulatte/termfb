#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "file.h"

int getntype(char *path) {
	struct stat st = {0};
	stat(path, &st);

	switch (st.st_mode & S_IFMT) {
		case S_IFDIR:
			return S_IFDIR;
	}
	
	// not dir, then
	return 0;
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
