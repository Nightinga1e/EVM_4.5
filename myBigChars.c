#include "myBigChars.h"

void bc_bigcharLayout(int64_t *A, int number)
{
  number = number%16;
  switch(number)
  {
    case 0:
      *A = 9114835285835153022;
      break;
    case 1:
      *A = 1736164148113840152;
      break;
    case 2:
      *A = 9114753724573974076;
      break;
    case 3:
      *A = 9114828792246861438;
      break;
    case 4:
      *A = 6944656713184996460;
      break;
    case 5:
      *A = 9114828792240963198;
      break;
    case 6:
      *A = 9108079987856408190;
      break;
    case 7:
      *A = 436317242630635134;
      break;
    case 8:
      *A = 9114835389317021310;
      break;
    case 9:
      *A = 9114828663398229630;
      break;
    case 10:
      *A = 7378724120842108476;
      break;
    case 11:
      *A = 9108079713924310654;
      break;
    case 12:
      *A = 9114729318785121918;
      break;
    case 13:
      *A = 4485134868898266686;
      break;
    case 14:
      *A = 9114729836194463358;
      break;
    case 15:
      *A = 434041554437832318;
      break;
    case 100:
      *A = 1736164587911780376;
      break;
    default:
      return;
    }
}

void bc_bigcharLayoutSTR(int64_t *A, char *string)
{
  for(int i = 0; i < 5; i++){
  char swchr = string[i];
  switch(swchr)
  {
    case '0':
      A[i] = 9114835285835153022;
      break;
    case '1':
      A[i] = 1736164148113840152;
      break;
    case '2':
      A[i] = 9114753724573974076;
      break;
    case '3':
      A[i] = 9114828792246861438;
      break;
    case '4':
      A[i] = 6944656713184996460;
      break;
    case '5':
      A[i] = 9114828792240963198;
      break;
    case '6':
      A[i] = 9108079987856408190;
      break;
    case '7':
      A[i] = 436317242630635134;
      break;
    case '8':
      A[i] = 9114835389317021310;
      break;
    case '9':
      A[i] = 9114828663398229630;
      break;
    case 'A':
      A[i] = 7378724120842108476;
      break;
    case 'B':
      A[i] = 9108079713924310654;
      break;
    case 'C':
      A[i] = 9114729318785121918;
      break;
    case 'D':
      A[i] = 4485134868898266686;
      break;
    case 'E':
      A[i] = 9114729836194463358;
      break;
    case 'F':
      A[i] = 434041554437832318;
      break;
    case '+':
      A[i] = 1736164587911780376;
      break;
    default:
      return;
    }
  }
}

int bc_printbigchar(int64_t big, int x, int y, enum colors clr1, enum colors clr2)
{
  int cntr = 1;
  int yOrig = y;
  int xOrig = x;
  mt_gotoXY(x, y);
  mt_setgbcolor(clr1);
  mt_setfgcolor(clr2);
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      if(big % 2)
        printf("\u2588");
      else
        printf(" ");
      big = big >> 1;
      mt_gotoXY(x, y+j+1);
    }
    x++;
    mt_gotoXY(x, y);
  }
  mt_setgbcolor(9);
  mt_setfgcolor(9);
}

int bc_getbigcharpos(int64_t big, int x, int y, int *value) // xy pomenyat mestami
{
	(*value) = (big >> (y * 8ull + x)) & 0x1;
	return 0;
}

int bc_setbigcharpos(int64_t *big, int64_t x, int64_t y, int value)
{
  if(value == 1)
    *big = *big | (1ull << (y * 8ull + x));
  if(value == 0)
    *big = *big & (~(1ull << (y * 8ull + x)));
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
  mt_gotoXY(y1, x1); //upper
  printf("\u250C");
  for(int i = 0; i < x2-x1; i++)
  {
    printf("\u2500");
  }
  printf("\u2510");

  for(int i = 0; i < y2-y1; i++) //leftright
  {
    mt_gotoXY(y1+i+1, x1);
    printf("\u2502");
    mt_gotoXY(y1+i+1, x2+1);
    printf("\u2502");
  }

  mt_gotoXY(y2+1, x1); //lower
  printf("\u2514");
  for(int i = 0; i < x2-x1; i++)
  {
    printf("\u2500");
  }
  printf("\u2518");
}

int bc_bigcharwrite(int64_t *container, int count)
{
  FILE *file = fopen("symbol", "wb");
	if(!file)
		return -121312;
  fwrite(container, sizeof(int64_t), count, file);
	fclose(file);
	return 0;
}

int bc_bigcharread(int64_t *containerOut, int need_count, int *count)
{
  //int64_t temp[4];
  *count = need_count;
  FILE *file1 = fopen("symbol", "rb");
  if(!file1)
		return -121312;
  //for(int h; h < 4; h++)
    //printf("\n>>BEFORE %ld", containerOut[h]);
	fread(containerOut, sizeof(containerOut), need_count, file1);
  //for(int h; h < 4; h++)
    //printf("\n>>AFTER %ld", containerOut[h]);
	fclose(file1);
  //printf("\n\n>>>>%ld<<<<<<", containerOut[0]);
  //printf("\n\nTEMP1%ld<<<<<<", temp[0]);
  //printf("\nTEMP2%ld<<<<<<", temp[1]);
	return 0;
}
