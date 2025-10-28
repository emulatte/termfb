default:
	gcc -o bin/termfb -Iinclude src/main.c src/display.c src/term.c && bin/termfb

debug:
	gcc -g -o bin/termfb -Iinclude src/main.c src/display.c src/term.c && gdb bin/termfb
