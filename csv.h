 char *csvgetline(FILE *f); 
char *csvfield(int n);
 int csvnfield(void);

enum { NOMEM = -2}; //Out of memory code

static char *line = NULL; //input chars
static char *sline = NULL; //line copy used by split;
static int maxline = 0; //size of line and sline;
static char **field = NULL; //field pointers\
static int maxfield = 0; //size of field[]
static int nfield = 0; // number of fields in field[]

static char fieldsep[] = ","; //field separator chars
