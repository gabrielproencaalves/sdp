#include <stdio.h>
#include "escapes.h"
#include "config.h"

static int CURSOR_X;    /* Current X cursor position */
static int CURSOR_Y;    /* Current Y cursor position */

#define CURSOR_FORWARD(x)  CUF((x)); CURSOR_X += (x);
#define CURSOR_BACKWARD(x) CUB((x)); CURSOR_X -= (x);
#define CURSOR_UPWARD(x)   CPL((x)); CURSOR_Y -= (x);
#define CURSOR_DOWNWARD(x) CNL((x)); CURSOR_Y += (x);

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
  if (   x < 1 || x > MAXWIDTH  - VMARGIN * 2
      || y < 1 || y > MAXHEIGHT - HMARGIN * 2)
    return;

  if (CURSOR_Y != y) {
    if (CURSOR_Y > y) {
      CURSOR_UPWARD(CURSOR_Y - y);
    }
    else {
      CURSOR_DOWNWARD(y - CURSOR_Y);
    }
  }

  if (CURSOR_X != x) {
    if (CURSOR_X > x) {
      CURSOR_BACKWARD(CURSOR_X - x);
    }
    else {
      CURSOR_FORWARD(x - CURSOR_X);
    }
  }
}
