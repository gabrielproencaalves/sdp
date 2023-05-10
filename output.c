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

static int CURSOR_Y; /* Current Y cursor position */
static int CURSOR_X; /* Current X cursor position */

/* initialize: set up panel and variables */
void initialize(void)
{
  int pos_y; /* line */
  int pos_x; /* column */

  for (pos_y = 0; pos_y < MAXHEIGHT; ++pos_y) {
    for (pos_x = 0; pos_x < MAXWIDTH; ++pos_x) {

      /* If pos_x and pos_y in the corner */
      if (   (pos_x < VMARGIN || pos_x > MAXWIDTH-VMARGIN-1)
          && (pos_y < HMARGIN || pos_y > MAXHEIGHT-HMARGIN-1))
	putchar(CORNER_CHAR); /* Print the corner char*/

      /* If pos_x in vert. margin */
      else if (pos_x < VMARGIN || pos_x > MAXWIDTH-VMARGIN-1)
	putchar(VSIDE_CHAR); /* Print the vert. margin char */

      /* If pos_y in hor. margin */
      else if (pos_y < HMARGIN || pos_y > MAXHEIGHT-HMARGIN-1)
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
