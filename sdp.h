/* initialize: set up panel and variables */
void initialize(void);

/* newline: print a newline on panel */
int newline(void);

/* printc(c): print the character c on panel*/
int printc(char);

/* prints(s): print the string s on panel */
int prints(char*);

/* movecur(x, y): moves the cursor to x and y */
void movecur(int, int);

/* clear: clears the panel */
void clear(void);

/* clearl:  clears the line or x characters */
void clearl(int);
