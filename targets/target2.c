#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
foo ( char *arg )
{
	char	buf[256];
	int	p, j, q, min, len;

	p = 290;
	q = strlen(arg);
	min = (q > p) ? p : q;
	len = min;
  
	for (j = 0; j <= len; j++)
		buf[j] = arg[j];

	return (0);
}

int
lab_main ( int argc, char *argv[] )
{
	int	t = 2;

	printf ("Target2 running.\n");

	if (argc != t)
	{
		fprintf ( stderr, "target2: argc != 2\n" );
		exit ( EXIT_FAILURE );
	}

	foo ( argv[1] );

	return (0);
}
