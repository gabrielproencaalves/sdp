#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdp.h"
#define MAX_WORD_ARGS 16
#define MAX_INPUT_BUFFER 256

char*  input_word_array[MAX_WORD_ARGS];
int    input_word_count;

int get_words(void)
{
  int c;
  int nc;
  char buf[MAX_INPUT_BUFFER];

  nc = 0;
  while ((c=getchar()) != EOF && input_word_count != MAX_WORD_ARGS) {
    if (c != ' ' && c != '\n' && nc < MAX_INPUT_BUFFER - 1)
      buf[nc++] = c;

    else {
      if (nc > 0) {
      	buf[nc++] = '\0';
      	input_word_array[input_word_count] = malloc(sizeof(int) * nc);
      	memmove(input_word_array[input_word_count++], buf, nc);
      	nc = 0;
      }
      if (c == '\n')
      	break;
    }
  }
  return input_word_count;
}

void clear_words(void)
{
  int i;
  for (i = 0; i < input_word_count; ++i)
    free(input_word_array[i]);
  input_word_count = 0;
}
