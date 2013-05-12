#include "zbPrint.h"

const char exec[100][100] = {
	"",
	"cpp main.c -o main.i" ,
	"cc1 main.i -o main.asm",
	"as main.asm -o main.o",
	""
};

int main() {
	long long long_pause = 100000;
	long long shrt_pause = 50000;

	zbInit();
	zbTick(shrt_pause);
	zbTitle(L"gcc (The GNU Compiler Collection)");
	zbPause();
	zbPrint(L"The GNU Compiler Collection includes front ends for C, C++, Objective-C, Fortran, Java, Ada, and Go, as well as libraries for these languages (libstdc++, libgcj,...)\n");
	zbPause();
	zbPrint(L"gcc invokes multiple programs => :\n");
	zbPause();

	zbTick(long_pause);
	zbPrint(L"\tcc1: c compiler ");
	zbTick(shrt_pause);
	zbPause();
	zbPrint(L"\t(.c => .asm)\n");
	zbPause();

	zbTick(long_pause); 
	zbPrint(L"\tas: assembler ");
	zbTick(shrt_pause);
	zbPause();
	zbPrint(L"\t\t(.asm => .o)\n");
	zbPause();

	zbTick(long_pause);
	zbPrint(L"\tcollect2:\n");
	zbPause();
	zbTick(shrt_pause);
	zbPrint(L"\t\tld: linker ");
	zbPause();
	zbPrint(L"\t(several .o => executable)\n");
	zbPause();

	zbStart();
	zbExit();
}
