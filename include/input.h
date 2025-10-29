#ifndef __INPUT__
#define __INPUT__
#include "display.h"
#include "term.h"

enum KEYS {
	MV_UP = 'k',
	MV_DOWN = 'j',
	MV_LEFT = 'h',
	MV_RIGHT = 'l',
	QUIT_TFB = 'q'
};

char handleinput(term *t, scr *s, char in);

void handlemove(term *t, scr *s, char direc);

char getinput();


#endif
