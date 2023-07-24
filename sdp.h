/* ======= OUTPUT ======= */

/* initialize: set up panel and variables */
void initialize(void);

/* newline: print a newline on panel */
int newline(void);

/* printc(c): print the character c on panel*/
int printc(char);

/* prints(s): print the string s on panel */
int prints(char*);

/* printsn(s, n): print s at maximum n characters */
int printsn(char*, int);

/* movecur(x, y): moves the cursor to x and y */
void movecur(int, int);

/* clearc(x): clears x characters */
void clearc(int);

/* clearl:  clears the line or x characters */
void clearl(void);

/* clear: clears the panel */
void clear(void);

/* ======= INPUT ======= */

/* readline: Reads at most x characters from stdin */
int readline(int);

/* prompt: print string and receive at most x characters from stdin */
int prompt(int, const char*);
