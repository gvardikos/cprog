int main(int argc, char **argv) {
  FILE *input;

  if (argc > 1) {
    if(!strcmp(argv[1],"-")) {
      input = stdin;
    } else {
      input = fopen(argv[1],"r");
      if (NULL == input) {
	fprintf(stderr, "Unable to open '%s': %s\n",
		argv[1], strerror(errno));
	exit(EXIT_FAILURE);
      }
    }
  } else {
    input = stdin;
  }

  printf("Size of file: %ld\n", getSizeOfInput(input));

  return EXIT_SUCCESS;
}
