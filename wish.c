#include "wish.h"

// 초기화 필요
const char* currentDirectory = "/home/";
const char** wishPATH;

int main() {
    const char* tmppath[16] = { "/bin", "/usr/bin" };
    wishPATH = tmppath;
    CMD input = NULL;
    size_t capacity = 0;
    
    const char** p = wishPATH;
    while(*p != '\0') {
        printf("%s\n", *p);
        p++;
    }
    exit(0);
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