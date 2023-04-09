#include "wish.h"

// 초기화 필요
const char* currentDirectory = "/home/";
const char** wishPATH;

int main() {
    const char* tmppath[16] = { "/bin", "/usr/bin" };
    wishPATH = tmppath;
    char* input = NULL;
    size_t capacity = 0;

    input = strdup("echo hello");

    char** array;
    size_t length = splitCommand(input, &array);

    size_t *outputL = NULL;
    CommandNode* node = parseCommand(array, length, outputL);
    printf("Result\n");
    while(node != NULL) {
        printf("CMD\n");
        printf(" - name : %s\n", node->command->cmd);
        printf(" - args : %ld\n", node->command->argc);
        printf(" - redirectTo : %s\n", node->command->redirectTo);
        node = node->next;
    }
    runCommand(node);

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
    fprintf(stderr, "%s", error_message);
    //write(stderr, error_message, strlen(error_message));
}