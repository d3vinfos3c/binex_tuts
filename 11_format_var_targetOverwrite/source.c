// gcc source.c -no-pie -fno-stack-protector -o chall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/stackvis.h"

long* addr;
long val;
long savedRet;
long* retAddr;

int main() {

    setbuf(stdin, (char*)0x0);
    setbuf(stdout, (char*)0x0);
    setbuf(stderr, (char*)0x0);

    char padding[8];
    char buff[128];
    long toModify = 0xdeadbeef;

    printf("\nYour goal is to modify the variable @ ");

    yellow();
    printf("0x%lx", (long)&buff + 136);
    reset_color();

    printf(" to equal ");
    
    yellow();
    printf("0xbeefc0de\n\n");
    reset_color();

    printf("This exercises is similar to the previous. You will notice a canary, but shouldn't have to worry about it!\n\n");

    memset(padding, 0xff, sizeof(padding));
    memset(buff, 0x00, sizeof(buff));
    show_stack(buff, 9, (long)&buff + 136);
    printf("\nEnter input: ");

    read(0, buff, 128);

    printf(buff);

    printf("\n");

    show_stack(buff, 9, (long)&buff + 136);

    if((int)toModify == 0xbeefc0de) {
        printf("\nCongrats! You modified the target variable!\n\n");
    }
    else {
        printf("\nYou failed to modify the target variable...\n\n");
    }

    exit(0);
}