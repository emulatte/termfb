default:
	gcc -o bin/termfb -Iinclude src/main.c src/display.c src/term.c && bin/termfb
