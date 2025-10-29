default:
	gcc -o bin/termfb -Iinclude src/main.c src/display.c src/input.c src/term.c && bin/termfb

debug:
	gcc -g -o bin/termfb -Iinclude src/main.c src/display.c src/term.c src/input.c && gdb bin/termfb
