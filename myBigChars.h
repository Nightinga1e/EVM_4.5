#ifndef myBigChars_h
#define myBigChars_h

#include <sys/ioctl.h>
#include <stdio.h>
#include "myTerm.h"
#include <inttypes.h>
#include <fcntl.h>

void bc_bigcharLayoutSTR(int64_t *, char *);
void bc_bigcharLayout(int64_t *, int);
int bc_box(int, int, int, int);
int bc_printbigchar(int64_t, int, int, enum colors, enum colors);
int bc_setbigcharpos(int64_t*, int64_t, int64_t, int);
int bc_getbigcharpos(int64_t, int, int, int*);
int bc_bigcharwrite(int64_t*, int);
int bc_bigcharread(int64_t*, int, int*);

#endif
