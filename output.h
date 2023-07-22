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
