// gcc source.c -no-pie -o chall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/stackvis.h"

long* addr;
long val;
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

    char padding[8];
    char buff[32];
    long toModify = 0xdeadbeef;

    printf("\nYour goal is to modify the return pointer @ "); 

    printf("0x%lx", (long)&buff + 56);

    printf(", to a function called '");

    printf("win");

    printf("' in the binary.\n\n");

    printf("This exercises is similar to the previous. You will notice a canary, but shouldn't have to worry about it!\n\n");

    retAddr = (long*)((long)&buff+56);
    savedRet = *retAddr;

    memset(padding, 0xff, sizeof(padding));
    memset(buff, 0x00, sizeof(buff));
    show_stack(buff, 4, (long)&buff + 56);
    printf("\nWhat would you like to write? ");

    fgets(buff, 30, stdin);

    val = atol(buff);

    printf("Where would you like to write it? ");

    fgets(buff, 30, stdin);

    addr = (long*)atol(buff);

    *addr = val;

    printf("\n");
    show_stack(buff, 4, (long)&buff + 56);

    if(savedRet == *retAddr) {
        printf("\nYou failed to overwrite the return pointer.\n\n");
    }

    return 0;
}