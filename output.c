#include <stdio.h>
#include "escapes.h"
#include "config.h"

static int CURSOR_X;    /* Current X cursor position */
static int CURSOR_Y;    /* Current Y cursor position */
static int LAST_PRINTL; /* Last printed line         */

/* This macro moves the cursor x times to the right
   and updates the variable CURSOR_X */
#define CURSOR_FORWARD(x) \
  do {                    \
    CUF((x));             \
    CURSOR_X += (x);      \
  } while (0)

/* This macro moves the cursor x times to the left
   and updates the variable CURSOR_X */
#define CURSOR_BACKWARD(x) \
  do {                     \
    CUB((x));              \
    CURSOR_X -= (x);       \
  } while (0)

/* This macro moves the cursor up x times
   and updates the variable CURSOR_Y */
#define CURSOR_UPWARD(x)         \
  do {                           \
    CPL((x));                    \
    CURSOR_Y -= (x);             \
    CUF(CURSOR_X + VMARGIN - 1); \
  } while (0)

/* This macro moves the cursor down x times
   and updates the variable CURSOR_Y */
#define CURSOR_DOWNWARD(x)       \
  do {                           \
    CNL((x));                    \
    CURSOR_Y += (x);             \
    CUF(CURSOR_X + VMARGIN - 1); \
  } while (0)

/* initialize: set up panel and variables */
void initialize(void)
{

#if (HMARGIN > 0) && (VMARGIN > 0)
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
    CNL(1);
  }
  CPL(MAXHEIGHT - HMARGIN); /* Go to the first empty */
  CUF(VMARGIN);             /* position inside square */
#endif

  CURSOR_X = CURSOR_Y = 1; /* Define x/y cursor coordinates */
}

/* newline: print a newline on panel */
int newline(void)
{
  /* If cursor is on last line */
  if (CURSOR_Y == MAXHEIGHT - HMARGIN - 1)
    return 0; /* Bad signal */

  CURSOR_DOWNWARD(1);  /* Move cursor down */
  CURSOR_BACKWARD(CURSOR_X - 1); /* Move cursor to first column */

  return 1; /* Good signal */
}

/* printc(c): print the character c on panel */
int printc(char c)
{
  /* If cursor reaches the margin or */
  /* the character to be printed is a newline */
  if ((CURSOR_X == MAXWIDTH - VMARGIN) || (c == '\n'))
    if (!newline())
      return 0;

  /* If the new line printed is less */
  /* than the variable LAST_PRINTL */
  if (CURSOR_Y > LAST_PRINTL)
    /* Update variable LAST_PRINTL */
    LAST_PRINTL = CURSOR_Y;

  putchar(c);
  CURSOR_X++;
  return c;
}

/* prints(s): print the string s on panel */
int prints(char *s)
{
  int i;

  /* Until reaching the end of s */
  for (i = 0; s[i] != '\0'; ++i)
    /* If chars cannot be printed */
    if (!printc(s[i]))
      return 0; /* Bad signal */

  return i; /* Return number of printed characters */
}

/* printsn(s, n): print s at maximum n characters */
int printsn(char* s, int n)
{
  int i;

  /* Until reaching the end of s and not passing the limit */
  for (i = 0; s[i] != '\0' && i < n; i++)
    /* If chars cannot be printed */
    if (!printc(s[i]))
      return 0; /* Bad signal */

  return i; /* Return number of printed characters */
}

/* movecur(x, y): moves the cursor to x and y */
void movecur(int x, int y)
{
  /* Checks if parameters extrapolate margin */
  if (x > MAXWIDTH || y > MAXHEIGHT)
    return;

  /* Just moves x if it is different of request */
  if (CURSOR_X != x) {
    if (CURSOR_X > x)
      CURSOR_BACKWARD(CURSOR_X - x);
    else
      CURSOR_FORWARD(x - CURSOR_X);
  }

  /* Just moves y if it is different of request */
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

  /* Clears the line */
  clearc(MAXWIDTH - VMARGIN * 2);

  CURSOR_BACKWARD(CURSOR_X - 1);
}

/* clear: clears the panel */
void clear(void)
{
  while (CURSOR_Y > 1) {
    clearl();
    CURSOR_UPWARD(1);
  }
  clearl();
}
