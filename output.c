#include <stdio.h>
#include "escapes.h"
#define MAXWIDTH  80 /* Default vt* width:         80 chars */
#define MAXHEIGHT 24 /* Default vt* height:        24 chars */
#define TABWIDTH  4  /* Default tab width:          4 spaces */
#define VMARGIN 1    /* Default vert. margin size:  1 char */
#define HMARGIN 1    /* Default hor. margin size:   1 char */
#define VSIDE_CHAR  '|'
#define HSIDE_CHAR  '-'
#define CORNER_CHAR '+'

static int CURSOR_Y;
static int CURSOR_X;

int initialize(void)
{
  int pos_y; /* line */
  int pos_x; /* column */

  for (pos_y = 0; pos_y < MAXHEIGHT; ++pos_y) {
    for (pos_x = 0; pos_x < MAXWIDTH; ++pos_x) {

      /* if pos_x and pos_y in the corner */
      if (   (pos_x < VMARGIN || pos_x > MAXWIDTH-VMARGIN-1)
          && (pos_y < HMARGIN || pos_y > MAXHEIGHT-HMARGIN-1))
	putchar(CORNER_CHAR); /* print the corner char*/

      /* if pos_x in vert. margin */
      else if (pos_x < VMARGIN || pos_x > MAXWIDTH-VMARGIN-1)
	putchar(VSIDE_CHAR); /* print the vert. margin char */

      /* if pos_y in hor. margin */
      else if (pos_y < HMARGIN || pos_y > MAXHEIGHT-HMARGIN-1)
	putchar(HSIDE_CHAR); /* print the hor. margin char */

      /* else, just print a space */
      else
	putchar(' ');
    }
    putchar('\n');
  }
  CPL(MAXHEIGHT - HMARGIN); /* go to the first empty */
  CUF(VMARGIN);             /* position inside square */

  CURSOR_X = CURSOR_Y = 1; /* define x/y cursor coordinates */
}

int prints(char *s);

int printc(int c);
