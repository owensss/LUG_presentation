#include <wchar.h>
/* print a string, one tick each character */
void zbPrint(const wchar_t* value);
/* set the tick, in mileseconds */
void zbTick(int milesecond);
/* pause, press any key to continue */
void zbPause(void);
/* start printing */
void zbStart(void);
/* init printing, shall be called before anyother functions */
void zbInit(void);
/* exit program */
void zbExit(void);
/* set title of the display. a title is a string printed in the middle
 of the first line, colored red */
void zbTitle(const wchar_t* title);
/* clear screen */
void zbClear(void);

#define main Main
