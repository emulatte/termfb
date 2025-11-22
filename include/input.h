#ifndef __INPUT__
#define __INPUT__

#include "fb.h"
#include "display.h"
#include "term.h"

enum KEYS {
	MV_UP = 'k',
	MV_DOWN = 'j',
	MV_LEFT = 'h',
	MV_RIGHT = 'l',
	SL_ENTER = '\r',
	QUIT_TFB = 'q'
};

void handlesel(fb *);

char handleinput(fb *f, char in);

void handlemove(fb *f, char direc);

char getinput();


#endif
