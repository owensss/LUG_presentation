#include "zbPrint.h"

int main () {
	zbInit();
	zbTick(100000);
	zbTitle(L"Outline");
	zbPause();
	zbPrint(L"\tgcc\n");
	zbPause();
	zbPrint(L"\tmake\n");
	zbPause();
	zbPrint(L"\tcmake");
	zbPause();
	zbStart();
	zbExit();
}
