// gcc source.c -no-pie -o chall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/stackvis.h"

long savedRet;
long* retAddr;
long canaryVal;
long* canaryAddr;

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

    yellow();
    printf("0x%lx", (long)&buff + 40);
    reset_color();

    printf(", to a function called '");

    yellow();
    printf("win");
    reset_color();

    printf("' in the binary.\n\n");

    canaryAddr = (long*)((long)&buff+24);
    canaryVal = *canaryAddr;

    printf("This is the first program you have seen with protections...\n\n");
    printf("This program has a canary (");

    yellow();
    printf("0x%lx", canaryVal);
    reset_color();

    printf(") @ ");

    yellow();
    printf("%p", canaryAddr);
    reset_color();

    printf(". The way to bypass this protection, and still overwrite\n");
    printf("the return pointer, is to append its value to your crafted payload at its relative postion in your payload.\n\n");

    retAddr = (long*)((long)&buff+40);
    savedRet = *retAddr;

    memset(padding, 0xff, sizeof(padding));
    memset(buff, 0x00, sizeof(buff));
    show_stack(buff, 3, (long)&buff + 40);
    printf("\nEnter input: ");

    read(0, buff, 50);

    printf("\n");
    show_stack(buff, 3, (long)&buff + 40);

    if(savedRet == *retAddr && canaryVal == *canaryAddr) {
        printf("\nYou failed to overwrite the return pointer and canary.\n\n");
    }
    else if(savedRet != *retAddr && canaryVal != *canaryAddr) {
        printf("\nYou overwrote the canary, but with the wrong value\n\n");
        exit(0);
    }

    return 0;
}