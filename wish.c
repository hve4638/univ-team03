#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wish.h>

int main() {
    char* buffer = NULL;
    size_t capacity = 0;

    while(1) {
        printf("wish> ");
        getline(&buffer, &capacity, stdin);
        printf("input: %s", buffer);
    }
}
