#include <stdio.h>

int main(int argc, char const *argv[]) 
{
  char filename[] = "config.txt";
  FILE *file = fopen ( filename, "r" );

  if (file != NULL) {
    char line [1000];
    while(fgets(line,sizeof line,file)!= NULL) /* read a line from a file */ {
      fprintf(stdout,"%s",line); //print the file contents on stdout.
    }

	char * pch;
	pch = strtok (line, " ");
	while (line != NULL)
	{
		printf ("%s\n",pch);
		pch = strtok (NULL, " ");
	}

    fclose(file);
  }
  else {
    perror(filename); //print the error message on stderr.
  }

	return 0;
}
	

