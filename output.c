#include <stdio.h>
#include "escapes.h"
#define MAXWIDTH  80 /* default vt* width */
#define MAXHEIGHT 24 /* default vt* height */

static int CURSOR_Y;
static int CURSOR_X;
