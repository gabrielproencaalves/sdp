#include <stdio.h>
#ifndef ESCAPES_H
#define ESCAPES_H
#define ESC "\x1b"
#define CSI "["
#define MAX_ESC_VAL 32767

/* cscreen: clear the entire screen */
#define cscreen()  printf(ESC CSI "2J");

/* curcline: clear the cursor line */
#define curcline() printf(ESC CSI "2K");

/* cline: clear the y-th line */
#define cline(y)   printf(ESC CSI "%i;H", (y)); curcline();

#endif
