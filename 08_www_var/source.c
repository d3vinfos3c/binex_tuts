// gcc source.c -no-pie -fno-stack-protector -o chall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/stackvis.h"

long* addr;
long val;

int main() {

    setbuf(stdin, (char*)0x0);
    setbuf(stdout, (char*)0x0);
    setbuf(stderr, (char*)0x0);

    char padding[8];
    char buff[32];
    long toModify = 0xdeadbeef;

    printf("\nYour goal is to modify the variable @ ");

    yellow();
    printf("0x%lx", (long)&buff + 40);
    reset_color();

    printf(" to equal ");
    
    yellow();
    printf("0xdeadc0de\n\n");
    reset_color();

    printf("This is a write-what-where exercise, and should not be trivial. This primitive is usually\n");
    printf("leveraged to overwrite entries on the GOT, or any writiable region of memory in the binary!\n\n");

    memset(padding, 0xff, sizeof(padding));
    memset(buff, 0x00, sizeof(buff));
    show_stack(buff, 3, (long)&buff + 40);
    printf("\nWhat would you like to write? ");

    fgets(buff, 30, stdin);

    val = atol(buff);

    printf("Where would you like to write it? ");

    fgets(buff, 30, stdin);

    addr = (long*)atol(buff);

    *addr = val;

    printf("\n");
    show_stack(buff, 3, (long)&buff + 40);

    if(toModify == 0xdeadc0de) {
        printf("\nCongrats! You modified the target variable!\n\n");
    }
    else {
        printf("\nYou failed to modify the target variable...\nMaybe you didn't supply enough input? Try again!\n\n");
    }

    exit(1);
}