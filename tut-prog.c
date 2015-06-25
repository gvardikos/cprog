#include <stdio.h>
#include <string.h>

char buf[200]; //input line buffer
char *field[20]; //fields

//declrations of functions
char *unquote(char *);
int csvgetline(FILE *);


//reads a line from the stdin
int csvgetline(FILE *fin)
{
  int nfield;
  char *p, *q;
      
  //fgets - read a line from a stream file (copy line, read line till n-1, file stream)
  if (fgets(buf, sizeof(buf),fin)==NULL)
    return -1;
  nfield = 0;
  //strtok(*string, separator) splits the string into tokens using the separator provided  
  for (q = buf; (p=strtok(q, ",\n\r")) != NULL; q = NULL)
    field[nfield++] = unquote(p);	
  return nfield;
}


char * unquote (char *p)
{
  if (p[0] == '"'){
    if (p[strlen(p)-1] == '"')
      p[strlen(p)-1] = '\0';
    p++;
  }  
  return p;
}



int main(void)
{
  int i, nf;
  
  while ((nf = csvgetline(stdin)) != -1)
    for (i = 0; i < nf; i++)
      printf("field[%d] = '%s'\n", i, field[i]);

  return 0;
}
