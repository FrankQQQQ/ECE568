#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "tmalloc.h"

int
foo ( char *arg )
{
	char *p;
	char *q;
	
	if ( (p = tmalloc(72)) == NULL)
	{
		fprintf(stderr, "tmalloc failure\n");
		exit(EXIT_FAILURE);
	}
	
	if ( (q = tmalloc(80)) == NULL)
	{
		fprintf(stderr, "tmalloc failure\n");
		exit(EXIT_FAILURE);
	} 
	
	tfree(p);
	tfree(q);
	
	if ( (p = tmalloc(152)) == NULL)
	{
		fprintf(stderr, "tmalloc failure\n");
		exit(EXIT_FAILURE);
	}
	
	strncpy(p, arg, 130);
	
	tfree(q);
	
	return (0);
}

int
lab_main ( int argc, char *argv[] )
{
	printf ("Target4 running.\n");
	if (argc != 2)
	{
		fprintf(stderr, "target4: argc != 2\n");
		exit(EXIT_FAILURE);
	}
  
	foo ( argv[1] );
	return (0);
}
