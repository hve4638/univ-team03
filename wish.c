#include "wish.h"

int main() {
    CMD input = NULL;
    size_t capacity = 0;

    while(1) {
        printf("wish> ");
        getline(&input, &capacity, stdin);

        CMDArray array;
        size_t length = splitCommand(input, &array);

        for(size_t i = 0; i < length; i++) {
            printf("%s\n", array[i]);
        }
        
        free(input); input = NULL;
        free(array); array = NULL;
    }
}

void error() {
    char error_message[30] = "An error has occurred\n";

    write(stderr, error_message, strlen(error_message));
}