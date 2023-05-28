#include <stdio.h>
#ifndef ESCAPES_H
#define ESCAPES_H

/* Maximum escapes parameters value */
#define MAX_ESC_VAL 32767

/* ESC: escape byte */
#define ESC "\x1b"

/* CSI: Control Sequence Introducer byte */
#define CSI "\x5b"

/* CUU: Cursor Up */
#define CUU(x)                                                     \
  if (x > 0)                                                       \
    printf(ESC CSI "%iA", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

/* CUD: Cursor Down */
#define CUD(x)                                                     \
  if (x > 0)                                                       \
    printf(ESC CSI "%iB", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

/* CUF: Cursor Forward */
#define CUF(x)                                                     \
  if (x > 0)                                                       \
    printf(ESC CSI "%iC", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

/* CUB: Cursor Back */
#define CUB(x)                                                     \
  if (x > 0)                                                       \
    printf(ESC CSI "%iD", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

/* CNL: Cursor Next Line */
#define CNL(x)                                                     \
  if (x > 0)                                                       \
    printf(ESC CSI "%iE", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

/* CPL: Cursor Previous Line */
#define CPL(x)                                                     \
  if (x > 0)                                                       \
    printf(ESC CSI "%iF", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

/* CHA: Cursor Horizontal Absolute */
#define CHA(x)                                                     \
  if (x > 0)                                                       \
    printf(ESC CSI "%iG", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

/* CUP: Cursor Position */
#define CUP(x)                                                       \
  if (x > 0)                                                         \
    printf(ESC CSI "%i;%iH", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x) \

/* ED: Erase Display */
#define ED() printf(ESC CSI "2J")

/* EL: Erase Line */
#define EL() printf(ESC CSI "2K")

/* SU: Scroll Up */
#define SU(x)                                                      \
  if (x > 0)                                                       \
    printf(ESC CSI "%iS", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

/* SD: Scroll Down */
#define SD(x)                                                      \
  if (x > 0)                                                       \
    printf(ESC CSI "%iT", ((x) > MAX_ESC_VAL) ? MAX_ESC_VAL : (x))

#endif
