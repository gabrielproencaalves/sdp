#include <stdio.h>
#include "escapes.h"
#define MAXWIDTH  80 /* Default vt* width:         80 chars */
#define MAXHEIGHT 24 /* Default vt* height         24 chars */
#define V_MARGIN  1  /* Default vertical margin:    1 char */
#define H_MARGIN  1  /* Default horizontal margin:  1 char */
#define TABWIDTH  4  /* Default: Tab = 4 spaces */

static int CURSOR_Y;
static int CURSOR_X;
static const char CORNER_CHAR = '+';
static const char VSIDE_CHAR  = '|';
static const char HSIDE_CHAR  = '-';

int initialize(void)
{
  int i;
  int j;

  for (i = 0; i < MAXWIDTH; ++i)
}

int prints(char *s);

int printc(int c)
{
  if (CURSOR_X == MAXWIDTH - 1) {
    CUD(1);
    CUB(MAXWIDTH - 2);
    CURSOR_Y++;
    CURSOR_X = 1;
  }
  putchar(c);
  return c;
}
