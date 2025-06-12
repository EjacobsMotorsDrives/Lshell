/*
 * TODO 
 * implement options 
 * print chars count
 * print lines count
 * print words counts
 * print all
 *
 *
 *
 * */



#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]){

  if (argc < 2 )
  {
    fprintf(stderr, "Usage: wc <filename>\n");
    return 1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (!fp)
  {
    perror("fopen");
    return 1;
  }

  int ch;
  int prev = ' ';
  int chars = 0;
  int words = 0;
  int lines = 0;

  while ((ch = fgetc(fp)) != EOF) 
  {
    chars++;
    if ( ch == '\n') lines++;
    if ( !isspace(ch) && isspace(prev)) words++;
    prev = ch;
  }

  fclose(fp);
  printf("Lines: %d, words: %d, Chars: %d\n", lines, words, chars);
 return 0;
}

