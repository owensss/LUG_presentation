#include "zbPrint.h"

int main () {
	zbInit();
	zbTick(100000);
	zbStart();
	zbTitle(L"CMake");
	zbPause();
	zbPrint(L"CMake is a family of tools designed to build, test and package software");
	zbPause();
	zbExit();
}

