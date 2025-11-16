default:
	gcc -o bin/termfb -Iinclude src/main.c src/display.c src/input.c src/term.c src/fb.c && bin/termfb

debug:
	gcc -g -o bin/termfb -Iinclude src/main.c src/display.c src/term.c src/input.c src/fb.c && gdb bin/termfb
