#include <stdio.h>
#include <string.h>

int  main(int argc, char *argv[])
{
  if (argc< 2)
  {
    fprintf(stderr, "Usage: cat <file>\n");
    return 1;
  }

  int  start     = 1;
  int  line_mode = 0;
  int  line_num  = 1;
  char buffer[1024];
  if ( argc > 1 && strcmp(argv[1], "-1") == 0)
  {
    line_mode = 1;
    start     = 2;
  }

  for (int i = start; i < argc; ++i)
  {
    FILE *fp = fopen(argv[i], "r");
    if (!fp)
    {
      perror(argv[i]);
      continue;
    }

     while (fgets(buffer, sizeof(buffer),fp))
     {
       if (line_mode) printf("%4d: ", line_num++);
       fputs(buffer, stdout);
     }
     fclose(fp);
   }
  
  return 0;
} 
