#include "MSC.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include <stdio.h>

void printHotkeys()
{
	mt_gotoXY(15, 50);
	bc_printA("L \u2014 LOAD");
	mt_gotoXY(16, 50);
	bc_printA("S \u2014 SAVE");
	mt_gotoXY(17, 50);
	bc_printA("R \u2014 RUN");
	mt_gotoXY(18, 50);
	bc_printA("T \u2014 STEP");
	mt_gotoXY(19, 50);
	bc_printA("I \u2014 RESET");
	mt_gotoXY(20, 50);
	bc_printA("F5 \u2014 ACCUMULATOR");
	mt_gotoXY(21, 50);
	bc_printA("F6 \u2014 INSTRUCTION COUNTER");
}

void printFlags()
{
	int value;
	mt_gotoXY(12, 64);
	sc_regGet(OVERFLOW, &value);
	if(value) bc_printA(" OV ");
	sc_regGet(ZERO_ERR, &value);
	if(value) bc_printA(" ZE ");
	sc_regGet(OUT_OF_MEM, &value);
	if(value) bc_printA(" OU ");
	sc_regGet(FREQ_ERR, &value);
	if(value) bc_printA(" FR ");
	sc_regGet(COMMAND_ERROR, &value);
	if(value) bc_printA(" CO ");
}

void printBigCharWindow(int Pointer)
{	
	int xx;
	int container[4];
	int B[2]={1579134,2115508224};
	int First[2]={0,0};
	int Second[2]={0,0};
	int Third[2]={0,0};
	int Fourth[2]={0,0};

//	bc_printbigchar(B, 15, 3, 5, 10);
	int temp = ram[Pointer];
	bc_bigcharLayout(First, (temp << 12) >> 12);
	bc_printbigchar(First, 15, 39, 5, 10);

	bc_bigcharLayout(Second, (temp << 8) >> 12);
	bc_printbigchar(Second, 15, 30, 5, 10);

	bc_bigcharLayout(Third, (temp << 4) >> 12);
	bc_printbigchar(Third, 15, 21, 5, 10);

	bc_bigcharLayout(Fourth, temp >> 12);
	bc_printbigchar(Fourth, 15, 12, 5, 10);
//////////////////////////////////////////////// set/getbigcharpos
/*
	bc_setbigcharpos(B, 2, 1, 1);
	bc_setbigcharpos(B, 6, 1, 1);	
	bc_setbigcharpos(B, 3, 1, 1);
	bc_setbigcharpos(B, 7, 1, 1);

	bc_setbigcharpos(B, 2, 4, 1);
	bc_setbigcharpos(B, 3, 4, 1);	
	bc_setbigcharpos(B, 4, 4, 1);
	bc_setbigcharpos(B, 5, 4, 1);
	bc_setbigcharpos(B, 6, 4, 1);
	bc_setbigcharpos(B, 1, 3, 1);
	bc_setbigcharpos(B, 7, 3, 1);
	bc_setbigcharpos(B, 2, 8, 1);
	bc_setbigcharpos(B, 6, 8, 1);
	bc_setbigcharpos(B, 3, 8, 1);
	bc_setbigcharpos(B, 7, 8, 1);

	bc_getbigcharpos(B, 2, 1, &xx);

	bc_printbigchar(B, 15, 3, 5, 10);
	mt_gotoXY(49,1);
	//printf("%d", xx); //getbigcharpos
*/
///////////////////////////////////////////////// save/load
unsigned int fd;
B[0]=1579134;
B[1]=2115508224;
fd = open("bigchar1.txt", O_WRONLY);
bc_bigcharwrite(fd, B, 1);
int count = 0;
B[0]=0;
B[1]=0;
fd = open("bigchar1.txt", O_RDONLY);
bc_bigcharread(fd, B, 1, &count);

bc_printbigchar(B, 15, 3, 5, 10);

mt_gotoXY(49,1);
printf("%d", count);
//////////////////////////////////////////////////

	mt_gotoXY(50,1);
}

void printMem(int x, int y, int Pointer)
{
	mt_gotoXY(x, y);
	for(int i = 0; i < 100; i++)
	{
		if(i == Pointer)
			mt_setgbcolor(5);
		else
			mt_setgbcolor(9);
		if(i%10 == 0)
		{
			if(i!=0)
			{
				bc_printA("\n"); printf("\033[%dC", y);
				
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
}

void printGraphics()
{
	mt_clrscr();
	bc_box(2, 2, 61, 12); // memory
	mt_gotoXY(2,29);
	printf("Memory:");

	bc_box(2,14,46,22); // bigchar

	bc_box(48,14,83,22); // keys
	mt_gotoXY(14,64);
	printf("Keys:");
	printHotkeys();

	bc_box(63,2,83,3); // accum
	mt_gotoXY(2,64);
	printf("Accumulator:");

	bc_box(63,5,83,6); //intruction
	mt_gotoXY(5,64);
	printf("InstructionCounter:");

	bc_box(63,8,83,9); //operation
	mt_gotoXY(8,64);
	printf("Operation:");

	bc_box(63,11,83,12); //flags
	mt_gotoXY(11,64);
	printf("Flags:");
	printFlags();
}


void RefreshWindow()
{
	mt_clrscr();
	printGraphics();
	printMem(3,2,Pointer);
	printBigCharWindow(Pointer);
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
	Pointer = 0;
	printMem(3,2,Pointer);
	printBigCharWindow(Pointer);
	int B[2]={1579134,2115508224};

	while(key != Quit)
	{
		rk_readkey(&key);
		if(key == Load)
		{
			sc_memoryLoad(fileLoad);
			RefreshWindow();
		}
		if(key == Save)
			sc_memorySave(fileSave);
		if(key == Input)
		{
			int temp;
			scanf("%d", &temp);
			sc_memorySet(Pointer, temp);
			RefreshWindow();
		}
		if(key == up)
		{
			if(!(Pointer - 10 < 0))
			{
				Pointer -= 10;
				RefreshWindow();
			}
		}
		if(key == down)
		if(!(Pointer + 10 > 99))
		{
			Pointer += 10;
			RefreshWindow();
		}
		if(key == left)
		{
			if(!(Pointer - 1 < 0))
			{
				Pointer -= 1;
				RefreshWindow();
			}
		}
		if(key == right)
		{
			if(!(Pointer + 1 > 99))
			{
				Pointer += 1;
				RefreshWindow();
			}
		}
	}
	mt_gotoXY(50,1);
	return 0;
}
