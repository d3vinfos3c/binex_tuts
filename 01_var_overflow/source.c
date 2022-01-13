// gcc source.c -fno-stack-protector -o chall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/stackvis.h"

int main() {

    setbuf(stdin, (char*)0x0);
    setbuf(stdout, (char*)0x0);
    setbuf(stderr, (char*)0x0);

    char padding[8];
    char buff[16];
    long toModify = 0xdeadbeef;

    printf("\nYour goal is to modify the variable @ ");

    printf("0x%lx\n\n", (long)&buff + 24);

    memset(padding, 0xff, sizeof(padding));
    memset(buff, 0x00, sizeof(buff));
    show_stack(buff, 2, (long)&buff + 24);
    printf("\nEnter input: ");

    fgets(buff, 32, stdin);

    printf("\n");
    show_stack(buff, 2, (long)&buff + 24);

    if(toModify != 0xdeadbeef) {
        printf("\nCongrats! You modified the target variable!\n\n");
    }
    else {
        printf("\nYou failed to modify the target variable...\nMaybe you didn't supply enough input? Try again!\n\n");
    }

    exit(0);
}