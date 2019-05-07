#include "MSC.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include <stdio.h>

void printHotkeys()
{
	mt_gotoXY(15, 50);
	printf("L \u2014 LOAD");
	mt_gotoXY(16, 50);
	printf("S \u2014 SAVE");
	mt_gotoXY(17, 50);
	printf("R \u2014 RUN");
	mt_gotoXY(18, 50);
	printf("T \u2014 STEP");
	mt_gotoXY(19, 50);
	printf("I \u2014 RESET");
	mt_gotoXY(20, 50);
	printf("F5 \u2014 ACCUMULATOR");
	mt_gotoXY(21, 50);
	printf("F6 \u2014 INSTRUCTION COUNTER");
}

void printFlags()
{
	int value;
	mt_gotoXY(12, 64);
	sc_regGet(OVERFLOW, &value);
	if(value) printf(" OV ");
	sc_regGet(ZERO_ERR, &value);
	if(value) printf(" ZE ");
	sc_regGet(OUT_OF_MEM, &value);
	if(value) printf(" OU ");
	sc_regGet(FREQ_ERR, &value);
	if(value) printf(" FR ");
	sc_regGet(COMMAND_ERROR, &value);
	if(value) printf(" CO ");
}

void printBigCharWindow(int memoryPointer)
{
	int64_t container[4];
	bc_printbigchar(1736164587911780376, 15, 3, 5, 10);
	int temp = ram[memoryPointer];
	bc_bigcharLayout(&container[0], temp >> 12);
	bc_bigcharLayout(&container[1], (temp << 4) >> 12);
	bc_bigcharLayout(&container[2], (temp << 8) >> 12);
	bc_bigcharLayout(&container[3], (temp << 12) >> 12);

	bc_printbigchar(container[0], 15, 12, 5, 10);
	bc_printbigchar(container[1], 15, 21, 5, 10);
	bc_printbigchar(container[2], 15, 30, 5, 10);
	bc_printbigchar(container[3], 15, 39, 5, 10);
	mt_gotoXY(50,1);
	//mt_setgbcolor(9);
}

void printMem(int x, int y, int memoryPointer)
{
	mt_gotoXY(x, y);
	for(int i = 0; i < 100; i++)
	{
		if(i == memoryPointer)
			mt_setgbcolor(5);
		else
			mt_setgbcolor(9);
		if(i%10 == 0)
		{
			if(i!=0)
			{
				printf("\n"); printf("\033[%dC", y);
			}
			else if(i == 0)
			{
				printf("\033[%dC", y-1);
			}
			printf("+%04x ", ram[i]);
		}
		else if(i%10 == 9)
			printf("+%04x", ram[i]);
		else
			printf("+%04x ", ram[i]);
	}
	mt_gotoXY(50,1);
	//mt_setgbcolor(9);
}

void printGraphics()
{
	mt_clrscr();
	bc_box(2, 2, 61, 12); /// membox
	mt_gotoXY(2,4);
	printf("Memory:");

	bc_box(2,14,46,22); /// graphics

	bc_box(48,14,83,22); /// keys
	mt_gotoXY(14,50);
	printf("Hotkeys:");
	printHotkeys();

	bc_box(63,2,83,3); /// rightboxes
	mt_gotoXY(2,65);
	printf("Accumulator:");

	bc_box(63,5,83,6);
	mt_gotoXY(5,65);
	printf("InstructionCounter:");

	bc_box(63,8,83,9);
	mt_gotoXY(8,65);
	printf("Operation:");

	bc_box(63,11,83,12);
	mt_gotoXY(11,65);
	printf("Flags:");
	printFlags();
}


void clearAndPrint()
{
	mt_clrscr();
	printGraphics();
	printMem(3,2,memoryPointer);
	printBigCharWindow(memoryPointer);
}

int main() {
    int temp;
	setbuf(stdout, NULL);
	int value;
	enum keys key = incorrectkey;
	int command = 0xa;
	int  operand = 0x1;
	char *fileSave = "memSave";
	char *fileLoad = fileSave;
	sc_regInit();
	sc_memoryInit();
	printGraphics();
	memoryPointer = 0;
	printMem(3,2,memoryPointer);
	printBigCharWindow(memoryPointer);
	while(key != Quit)
	{
		rk_readkey(&key);
		if(key == Load)
		{
			sc_memoryLoad(fileLoad);
			clearAndPrint();
		}
		if(key == Save)
			sc_memorySave(fileSave);
		if(key == Input)
		{
			int temp;
			scanf("%d", &temp);
			sc_memorySet(memoryPointer, temp);
			clearAndPrint();
		}
		if(key == up)
		{
			if(!(memoryPointer - 10 < 0))
			{
				memoryPointer -= 10;
				clearAndPrint();
			}
		}
		if(key == down)
		if(!(memoryPointer + 10 > 99))
		{
			memoryPointer += 10;
			clearAndPrint();
		}
		if(key == left)
		{
			if(!(memoryPointer - 1 < 0))
			{
				memoryPointer -= 1;
				clearAndPrint();
			}
		}
		if(key == right)
		{
			if(!(memoryPointer + 1 > 99))
			{
				memoryPointer += 1;
				clearAndPrint();
			}
		}
	}
	mt_gotoXY(50,1);
	return 0;
}
