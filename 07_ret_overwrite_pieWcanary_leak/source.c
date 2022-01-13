// gcc source.c -o chall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/stackvis.h"

long savedRet;
long* retAddr;
long canaryVal;
long* canaryAddr;
long hint;

void win() {
    printf("\nCongrats, you successuly changed execution flow!\n");
    exit(0);
}

int main() {

    setbuf(stdin, (char*)0x0);
    setbuf(stdout, (char*)0x0);
    setbuf(stderr, (char*)0x0);

    long* hintAddr = &hint;
    char padding[16];
    char buff[16];

    canaryAddr = (long*)((long)&buff+24);
    canaryVal = *canaryAddr;

    printf("\nYour goal is to modify the return pointer @ "); 

    printf("0x%lx", (long)&buff + 40);

    printf(", to a function called '");

    printf("win");

    printf("' in the binary.\n\nThis binary has PIE enabled and a canary, you must bypass both via a leak. You can leak both in one shot.\n");
    printf("Especially if you have a good understanding of format strings.\n\n");

    retAddr = (long*)((long)&buff+40);
    savedRet = *retAddr;

    memset(padding, 0xff, sizeof(padding));
    memset(buff, 0x00, sizeof(buff));
    show_stack_hideCanary(buff, 3, (long)&buff + 40, (long)canaryAddr);

    printf("\nEnter your name: ");

    scanf("%s[^\n]", buff);

    printf("Hello, ");
    printf(buff);
    printf(". Good luck!\n\n");

    printf("\nEnter input: ");

    read(0, buff, 50);

    printf("\n");
    show_stack_hideCanary(buff, 3, (long)&buff + 40, (long)canaryAddr);

    if(savedRet == *retAddr && canaryVal == *canaryAddr) {
        printf("\nYou failed to overwrite the return pointer and canary.\n\n");
    }

    else if(savedRet != *retAddr && canaryVal != *canaryAddr) {
        printf("\nYou overwrote the canary, but with the wrong value!\n\n");
        exit(0);
    }

    return 0;
}