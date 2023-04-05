#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wish.h"

int main() {
    CMD input = NULL;
    size_t capacity = 0;

    while(1) {
        printf("wish> ");
        getline(&input, &capacity, stdin);

        size_t length;
        CMDArray cmd;
        length = splitCommand(cmd, input);
    }
}
