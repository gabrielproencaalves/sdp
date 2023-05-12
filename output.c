#include <stdio.h>
#include "escapes.h"
#define MAXWIDTH     80 /* Default vt* width:          80  chars  */
#define MAXHEIGHT    24 /* Default vt* height:         24  chars  */
#define TABWIDTH      4 /* Default tab width:           4  spaces */
#define VMARGIN       1 /* Default vert. margin size:   1  char   */
#define HMARGIN       1 /* Default hor. margin size:    1  char   */
#define VSIDE_CHAR  '|' /* Default vert. margin char:  '|'        */
#define HSIDE_CHAR  '-' /* Defaukt hor. margin char:   '-'        */
#define CORNER_CHAR '+' /* Default corner margin char: '+'        */

static int CURSOR_X;    /* Current X cursor position */
static int CURSOR_Y;    /* Current Y cursor position */

/* initialize: set up panel and variables */
void initialize(void)
{

  for (CURSOR_Y = 0; CURSOR_Y < MAXHEIGHT; ++CURSOR_Y) {
    for (CURSOR_X = 0; CURSOR_X < MAXWIDTH; ++CURSOR_X) {

      /* If CURSOR_X and CURSOR_Y in the corner */
      if (   (CURSOR_X < VMARGIN || CURSOR_X > MAXWIDTH-VMARGIN-1)
          && (CURSOR_Y < HMARGIN || CURSOR_Y > MAXHEIGHT-HMARGIN-1))
	putchar(CORNER_CHAR); /* Print the corner char*/

      /* If CURSOR_X in vert. margin */
      else if (CURSOR_X < VMARGIN || CURSOR_X > MAXWIDTH-VMARGIN-1)
	putchar(VSIDE_CHAR); /* Print the vert. margin char */

      /* If CURSOR_Y in hor. margin */
      else if (CURSOR_Y < HMARGIN || CURSOR_Y > MAXHEIGHT-HMARGIN-1)
	putchar(HSIDE_CHAR); /* Print the hor. margin char */

      /* Else, just print a space */
      else
	putchar(' ');
    }
    putchar('\n');
  }
  CPL(MAXHEIGHT - HMARGIN); /* Go to the first empty */
  CUF(VMARGIN);             /* position inside square */

  CURSOR_X = CURSOR_Y = 1; /* Define x/y cursor coordinates */
}

/* printc(c): print the character c on panel*/
int printc(char c)
{
  /* If cursor reaches the margin or */
  /* the character to be printed is a newline*/
  if ((CURSOR_X == MAXWIDTH - VMARGIN) || (c == '\n'))
    if (!newline()) /* If unable to print newline */
      return 0; /* Bad signal */
  putchar(c);
  CURSOR_X++;
  return c;
}

/* prints(s): print the string s on panel */
int prints(char *s)
{
  int i;

  for (i = 0; s[i] != '\0'; ++i) /* Until reaching the end of s */
    if(!printc(s[i])) /* If chars cannot be printed */
      return 0; /* Bad signal */
  return i; /* Return number of printed characters */
}

/* newline: print a newline on panel */
int newline(void)
{
  /* If cursor is on last line */
  if (CURSOR_Y == MAXHEIGHT - HMARGIN - 1)
    return 0; /* Bad signal */
  CNL(1); /* Move cursor down */
  CUF(VMARGIN); /* Move cursor forward to inside panel */
  CURSOR_X = 1;
  CURSOR_Y++;
  return 1; /* oh yeah */
}

void movecur(int x, int y)
{
  if (CURSOR_Y != y)
    CURSOR_X = 0;

  while (CURSOR_Y != y) {
    if (CURSOR_Y > y) {
      CPL(1);
      --CURSOR_Y;
    }
    else {
      CNL(1);
      ++CURSOR_Y;
    }
  }
  while (CURSOR_X != x) {
    if (CURSOR_X > x) {
      CUB(1);
      --CURSOR_X;
    }
    else {
      CUF(1);
      ++CURSOR_X;
    }
  }
}
