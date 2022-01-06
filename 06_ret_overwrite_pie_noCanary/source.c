// gcc source.c -fno-stack-protector -o chall
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/stackvis.h"

long savedRet;
long* retAddr;
long hint = 0xdeadbeef;

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

    printf("The next protection you will learn, is position-independent code (PIC) or more often position-independent executable (PIE)\n");
    printf("Previoiously the base address of the binaries was 0x40000. This time this address will look something like '0x558b5e6ff000'.\n");
    printf("This is bypassed by leaking an address, determining the base address from the leak, and then determining any addresses to code\nfrom their offsets. If you are confused by any of this, do some research to better understand it!\n\n");
    printf("Like last time, we will start with a hint @ ");
    
    yellow();
    printf("%p\n\n", &hint);
    reset_color();


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