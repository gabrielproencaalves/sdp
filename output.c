#include <stdio.h>
#include "escapes.h"
#include "config.h"

static int CURSOR_X;    /* Current X cursor position */
static int CURSOR_Y;    /* Current Y cursor position */
static int LAST_PRINTL; /* Last printed line         */

#define CURSOR_FORWARD(x) \
  do {                    \
    CUF((x));             \
    CURSOR_X += (x);      \
  } while (0)

#define CURSOR_BACKWARD(x) \
  do {                     \
    CUB((x));              \
    CURSOR_X -= (x);       \
  } while (0)

#define CURSOR_UPWARD(x)         \
  do {                           \
    CPL((x));                    \
    CURSOR_Y -= (x);             \
    CUF(CURSOR_X + VMARGIN - 1); \
  } while (0)

#define CURSOR_DOWNWARD(x)       \
  do {                           \
    CNL((x));                    \
    CURSOR_Y += (x);             \
    CUF(CURSOR_X + VMARGIN - 1); \
  } while (0)

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

/* newline: print a newline on panel */
int newline(void)
{
  /* If cursor is on last line */
  if (CURSOR_Y == MAXHEIGHT - HMARGIN - 1)
    return 0; /* Bad signal */

  CURSOR_DOWNWARD(1);  /* Move cursor down */
  CURSOR_BACKWARD(CURSOR_X - 1); /* move cursor to first column */

  return 1; /* oh yeah */
}

/* printc(c): print the character c on panel*/
int printc(char c)
{
  /* If cursor reaches the margin or */
  /* the character to be printed is a newline*/
  if ((CURSOR_X == MAXWIDTH - VMARGIN) || (c == '\n'))
    return (!newline()) ? 0 : 1;


  if (CURSOR_Y > LAST_PRINTL)
    LAST_PRINTL = CURSOR_Y;

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

/* movecur(x, y): moves the cursor to x and y */
void movecur(int x, int y)
{
  if (x > MAXWIDTH || y > MAXHEIGHT)
    return;

  if (CURSOR_X != x) {
    if (CURSOR_X > x)
      CURSOR_BACKWARD(CURSOR_X - x);
    else
      CURSOR_FORWARD(x - CURSOR_X);
  }

  if (CURSOR_Y != y) {
    if (CURSOR_Y > y)
      CURSOR_UPWARD(CURSOR_Y - y);
    else
      CURSOR_DOWNWARD(y - CURSOR_Y);
  }
}

/* clearc(x): clears x characters */
void clearc(int x)
{
  while (x--)
    printc(' ');
}

/* clearl:  clears the line */
void clearl(void)
{
  CURSOR_BACKWARD(CURSOR_X - 1);
  clearc(MAXWIDTH - VMARGIN * 2);
  CURSOR_BACKWARD(CURSOR_X - 1);
}
