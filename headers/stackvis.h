void reset_color() {
  printf("\033[0m");
}

void black () {
  printf("\033[1;30m");
}

void red () {
  printf("\033[1;31m");
}

void green () {
  printf("\033[1;32m");
}

void yellow () {
  printf("\033[1;33m");
}

void blue () {
  printf("\033[1;34m");
}

void purple () {
  printf("\033[1;35m");
}

void cyan () {
  printf("\033[1;36m");
}

void white () {
  printf("\033[1;37m");
}

void test() {
    cyan();
    printf("Hello world!\n");
}

void print_16_bytes(void* addr, long goal) {
    long* buff = (long*)addr;
    for(int i = 0; i < 2; i++) {

        if((long)&buff[i] == goal) {
          red();
        }

        printf("0x%016lx ", buff[i]);

        reset_color();
    }
}

void show_stack(char* buff, int n, long goal) {
    for(int i = 0; i < n; i++) {
        cyan();
        printf("%p", (buff + (16 * i)));
        reset_color();
        printf(": ");
        print_16_bytes((void *)(buff + (16 * i)), goal);
        printf("\n");
    }
}

void show_stack_hideCanary(char* buff, int n, long goal, long canary) {
    for(int i = 0; i < n; i++) {
        cyan();
        printf("%p", (buff + (16 * i)));
        reset_color();
        printf(": ");
        print_16_bytes_hideCanary((void *)(buff + (16 * i)), goal, canary);
        printf("\n");
    }
}

void print_16_bytes_hideCanary(void* addr, long goal, long canary) {
    long* buff = (long*)addr;
    for(int i = 0; i < 2; i++) {

        if((long)&buff[i] == goal) {
          red();
        }
        
        if((long)&buff[i] == canary) {
          green();
          printf("*****REDACTED*****");
        }
        else {
          printf("0x%016lx ", buff[i]);
        }

        reset_color();
    }
}