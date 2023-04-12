#include "wish.h"

const char** wishPATH;
size_t wishPATHCount;

static void Run(char*);
static void RunInteractive();
static void RunBatch(FILE*);

void wish(FILE* file) {
    const char* tmppath[1024] = { strdup("/bin"), };
    wishPATH = tmppath;
    wishPATHCount = 1;
    if (file == stdin) RunInteractive();
    else RunBatch(file);

    for(size_t i = 0; i < wishPATHCount; i++) {
        char* p = (char*)wishPATH[i];
        wishPATH[i] = NULL;
        free(p);
    }
}

void Error() {
    char error_message[30] = "An error has occurred\n";
    fprintf(stderr, "%s", error_message);
}

void RunBatch(FILE* input) {
    char* rawCmd = NULL;
    size_t capacity = 0;

    while(1) {
        if (getline(&rawCmd, &capacity, input) == -1) break;
        Run(rawCmd);
        free(rawCmd);
        rawCmd = NULL;
    }
}

void RunInteractive() {
    char* rawCmd = NULL;
    size_t capacity = 0;

    while(1) {
        printf("wish> ");
        if (getline(&rawCmd, &capacity, stdin) == -1) break;
        Run(rawCmd);
        free(rawCmd);
        rawCmd = NULL;
    }
}

void Run(char* rawCmd) {
    char** splitted = NULL;
    size_t length = splitCommand(rawCmd, &splitted);
    
    if (length != 0) {
        CommandNode* node = parseCommand(splitted, length);
        if (node == NULL) {
            Error();
        } else {
            runCommand(node);
            freeCommandNode(node);
        }
    }

    free(splitted);
}
