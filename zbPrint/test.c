#include "zbPrint.h"

int main(int argc, const char* argv) {
	zbInit();
	zbTick(100000);
	zbPrint(L"中文\n");
	zbPause();
	zbTick(100000);
	zbPrint(L"another中文\n");
	zbTick(10000);
	zbPause();
	zbPrint(L"哈哈个哥哥another中文\n");
	zbStart();
	zbPause();
	zbExit();
	// zbPause();
}
