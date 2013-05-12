#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>
#include "zbPrint.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <ncursesw/ncurses.h>

long long tick;
timer_t timerid;
// op types
#define CHAR_BUFFER 5000
#define PRINT 0
#define START 1
#define PAUSE 2
#define TICK  3
#define CLEAR 4
#define EXIT  -1
struct outlist { // op storer
	int type;
	wchar_t* str; // output string
	long long tick; // only used when outlist.type==TICK
} *strlist;
int strtotal = 0; // total
int str_current = 0; // string current position, related to outlist.str
int current_count = 0;

wchar_t* title = NULL; // title: string in the middle of the first line, colored red

static void settitle(void);

static void setTick(long long tick_) {
	struct itimerspec its;
	its.it_value.tv_sec = tick_ / 1000000000ll;
	its.it_value.tv_nsec = tick_ % 1000000000ll;

	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;

	timer_settime(timerid, 0, &its, NULL);
}

static void print(int sig, siginfo_t *si, void *uc) {
	if (str_current == strtotal) {
		return;
	} 

	int type = strlist[str_current].type;
	if (type == PAUSE) { // PAUSE
		signal(sig, SIG_IGN); // disable signal
		getch(); // wait for anykey
		signal(sig, (void*)print); // enable signal
		++str_current;
	} else if (type == TICK) { // set tick
		setTick(strlist[str_current].tick) ;
		++str_current;
	} else if (type == EXIT) { // exit
		printw("\n");
		endwin();
		exit(0);
	} else if (type == CLEAR) { // clear
		clear();
		settitle();
		++str_current;
	} else if (strlist[str_current].type == PRINT) { // print
		if (wcslen(strlist[str_current].str) > current_count) {
			printw("%lc", strlist[str_current].str[current_count++]);
			refresh();
		} else if (current_count == wcslen(strlist[str_current].str)) { // current string ends
			++str_current;
			current_count = 0;
		}
	}
}

void zbInit(void) {
	setlocale(LC_ALL, "zh_CN.utf-8");
	initscr();
	use_default_colors();
	noecho();
	struct sigevent sev;
	struct sigaction sa;

	// set handler
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = print;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGRTMIN, &sa, NULL);

	// create timer
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = &timerid;
	timer_create(CLOCK_REALTIME, &sev, &timerid);

	// malloc string buffer
	strlist = (struct outlist*) malloc(sizeof(struct outlist*)*CHAR_BUFFER);
}

void zbTick(int tick_) {
	strlist[strtotal].type = TICK;
	strlist[strtotal].str = NULL;
	strlist[strtotal].tick = tick_ * 1000; // to msec
	++strtotal;
}

void zbPause(void) {
	strlist[strtotal].type = PAUSE;
	strlist[strtotal].str = NULL;
	++strtotal;
}

void zbStart() {
	setTick(10000);
}

void zbExit(void) {
	strlist[strtotal].type = EXIT;
	++strtotal;
}

void zbClear(void)  {
	strlist[strtotal].type = CLEAR;
	++strtotal;
}

void zbPrint(const wchar_t* value) {
	
	strlist[strtotal].str = (wchar_t*) malloc(sizeof(wchar_t)*(wcslen(value)+1));
	// copy
	wcscpy(strlist[strtotal].str, value);
	strlist[strtotal].type = PRINT;
	++strtotal;
}

static void settitle(void) {
	if (title == NULL) {
		return;
	}
	int col= stdscr? stdscr->_maxx+1 : -1; // manually preprocessed from getmaxyx
	start_color();
	init_pair(1, COLOR_RED, COLOR_WHITE);
	attron(A_BOLD | COLOR_PAIR(1)); // set color, set bold
	mvprintw(0, (col-wcslen(title))/2, "%ls", title);
	attroff(A_BOLD | COLOR_PAIR(1));
	addch('\n');
}

void zbTitle(const wchar_t* title_) {
	if (title) free(title);
	if (! title_) { // _title is null
		title = NULL;
		return ;

	}
	title = (wchar_t*) malloc(sizeof(wchar_t)*(wcslen(title_)+1));
	wcscpy(title, title_); // copy into title
	settitle();
}

#undef main
int Main(int argc, const char* argv);
int main(int argc, const char* argv) {
	Main(argc, argv);
	while (1);
	return 0;
}
