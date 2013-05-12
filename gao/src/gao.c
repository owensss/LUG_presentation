#include "gao7.h"
#include "gao8.h"
#include "zbPrint.h"

int main() {
	zbInit();
	zbTick(100000);
	gao7();
	gao8();
	zbPause();
	zbStart();
	zbExit();
}
