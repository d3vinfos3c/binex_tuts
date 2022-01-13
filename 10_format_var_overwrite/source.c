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
    char buff[32];
    long toModify = 0xdeadbeef;

    printf("\nYour goal is to modify the variable @ ");

    printf("0x%lx\n\n", (long)&buff + 40);

    puts("This exercise is to modify the variable using the '%n\\%hn\\%hhn' format specifier.\n\n");

    memset(padding, 0xff, sizeof(padding));
    memset(buff, 0x00, sizeof(buff));
    show_stack(buff, 3, (long)&buff + 40);
    printf("\nEnter input: ");

    read(0, buff, 32);

    printf(buff);

    printf("\n");

    show_stack(buff, 3, (long)&buff + 56);

    if(toModify != 0xdeadbeef) {
        printf("\nCongrats! You modified the target variable!\n\n");
    }
    else {
        printf("\nYou failed to modify the target variable...\nMaybe you didn't supply enough input? Try again!\n\n");
    }

    exit(0);
}