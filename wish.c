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

        CMDArray cmd;
        size_t capa = 0;
        size_t length = splitCommand(input, cmd, &capa);
    }
}
