#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char *csvgetline(FILE *f);
extern char *csvfield(int n);
extern int csvnfield(void);

static void reset (void);
static int endofline (FILE *f, int);
static char *advquoted(char *);
static int split(void);


enum { NOMEM = -2 };

static char *line = NULL;
static char *sline = NULL;
static int maxline = 0;
static char **field = NULL;
static int maxfield = 0;
static int nfield = 0;

static char fieldsep[] = "\t";


char *csvgetline(FILE *fin){
  int i, c;
  char *newl, *news;

  if (line == NULL){
    maxline = maxfield = 1;
    line = (char *) malloc (maxline);
    sline = (char *) malloc (maxline);
    field = (char **) malloc (maxfield * sizeof(field[0]));
    
    if (line == NULL || sline == NULL || field == NULL){
      reset();
      return NULL; //Out of memory
    }
  }
  
  for (i=0; (c=getc(fin)) != EOF && !endofline(fin,c); i++){
      if (i>=maxline-1){
	maxline *= 2;
	newl = (char *) realloc (line, maxline);
	news = (char *) realloc (sline, maxline);
	
	if (newl == NULL || news == NULL){
	  reset();
	  return NULL; //out of memory
	}
	line = newl;
	sline = news;
      }
      line[i] = c;
  }//end for
  
  line[i]='\0';
  
  if (split() == NOMEM){
    reset();
    return NULL; //out of memory
  }
  
  return (c == EOF && i == 0) ? NULL : line;
}//end of function



static void reset(void){
  free(line);
  free(sline);
  free(field);
  line = NULL;
  sline = NULL;
  field = NULL;
  maxline = maxfield = nfield = 0;
}



static int endofline(FILE *fin, int c){
  int eol;
  
  eol = (c=='\r' || c=='\n');
  if (c == '\r'){
    c = getc(fin);
    if (c != '\n' && c != EOF)
      ungetc(c,fin); //read too far; put c back
  }
  return eol;
}



static int split(void){
  char *p, **newf;
  char *sepp; //pointer to temporary separator character
  int sepc; //temporary separator character
 
 nfield = 0;
  
  if (line[0] == '\0')
    return 0;

  strcpy (sline, line);
  p = sline;
  
  do {
    if (nfield >= maxfield){
      maxfield *= 2; 
      newf = (char **) realloc (field, maxfield * sizeof (field[0]));
      
      if (newf == NULL)
	return NOMEM;
      
      field = newf;
    }
    
    if (*p == '"'||*p == ',')
      sepp = advquoted(++p);
    else
      sepp = p +strcspn(p, fieldsep);
    sepc = sepp[0];
    sepp[0] = '\0'; //terminate field;
    field[nfield++] = p;
    p = sepp +1;
  } while (sepc == '\t');
  
  return nfield;
}




static char *advquoted(char *p){
  int i, j;
  
  for (i = j = 0; p[j] != '\0'; i++, j++){
    if (p[j] == '"' && p[++j] != '"') {
      //copy up to next separator or \0
      int k = strcspn(p+j, fieldsep);
      memmove(p+i, p+j, k);
      i+=k;
      j+=k;
      break;
    }
    p[i] = p[j];
  }//end for
  
  p[i] = '\0';
  return p+j;
}


char *csvfield(int n) {
  if (n <0 || n>= nfield)
    return "\t";
  
  return field[n];
}

int csvnfield(void){
  return nfield;
}

//------------------ MAIN -----------------------//
int main (int a, char *b[]){
  int i;
  char *line;
  FILE *thefile;
  char *str;
  
  if (a == 2){
    thefile = fopen(b[1], "r");    
    
    if (thefile == 0 || thefile == NULL){
      fprintf(stderr, "Unable to open '%s'\n",b[1]);
      exit(0);
    }    
    
    while((line = csvgetline(thefile)) != NULL){
      str=strjoin(field,'\t');
      //printf("Line is '%s' \n", line);
      printf("%s\n",str);
      
      //for (i = 0; i< csvnfield(); i++){
      //if there is no other element in the fields array dont print tab
      //if (i == csvnfield()-1)
      //printf("%s",csvfield(i));
      //else
      //  printf("%s\t",csvfield(i));
      //}
      //printf("\n");
    }
  }
  else{
    //to-do 
  }
  
  

  
  /*
    while((line = csvgetline(stdin)) != NULL){
    printf("line = '%s' \n", line);
    
    for (i = 0; i< csvnfield(); i++)
    printf("field[%d] = '%s'\n", i, csvfield(i));
    }*/
  
  return 0;
}



