// gcc source.c -fno-stack-protector -no-pie -o chall 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/stackvis.h"

long savedRet;
long* retAddr;

void win() {
    printf("\nCongrats, you successuly changed execution flow!\n");
    exit(0);
}

int main() {

    setbuf(stdin, (char*)0x0);
    setbuf(stdout, (char*)0x0);
    setbuf(stderr, (char*)0x0);

    char padding[16];
    char buff[16];

    printf("\nYour goal is to modify the return pointer @ "); 

    printf("0x%lx", (long)&buff + 40);

    printf(", to a function called '");

    printf("win");

    printf("' in the binary.\n\n");
    printf("A good tool to use is 'objdump'. Now is the time to learn more about it, if you don't!\n\n");

    retAddr = (long*)((long)&buff+40);
    savedRet = *retAddr;

    memset(padding, 0xff, sizeof(padding));
    memset(buff, 0x00, sizeof(buff));
    show_stack(buff, 3, (long)&buff + 40);
    printf("\nEnter input: ");

    read(0, buff, 50);

    printf("\n");
    show_stack(buff, 3, (long)&buff + 40);

    if(savedRet == *retAddr) {
        printf("\nYou failed to overwrite the return pointer.\n\n");
    }

    return 0;
}