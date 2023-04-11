#include <unistd.h>
#include <errno.h>
#include "wish.h"

static void CD(Command* command) {
    if (command->argc == 0 || command->argc > 1) Error();
    else if (chdir(command->args[0]) == -1) Error();
}

static void Path(Command* command) {
    size_t size = command->argc;
    clearWishPATH();

    for(size_t i=0; i<size; i++) {
        const char* path = command->args[i];

        if (path[0] == '/') {
            wishPATH[wishPATHCount++] = strdup(path);
        } else {
            char* buffer = realpath(path, NULL);
            wishPATH[wishPATHCount++] = buffer;
        }
    }
}

void clearWishPATH() {
    for(size_t i = 0; i < wishPATHCount; i++) {
        char *p = (char*)wishPATH[i];
        wishPATH[i] = NULL;
        free(p);
    }
    wishPATHCount = 0;
}

static void Exit(Command* command) {
    if (command->argc == 0) exit(0);
    else Error();
}

int isBuiltInCommand(Command* command) {
    const char* cmd = command->cmd;

    if (strcmp(cmd, "cd") == 0) return 1;
    if (strcmp(cmd, "exit") == 0) return 1;
    if (strcmp(cmd, "path") == 0) return 1;
    return 0;
}

void runBuiltInCommand(Command* command) {
    const char* cmd = command->cmd;

    if (strcmp(cmd, "cd") == 0) CD(command);
    else if (strcmp(cmd, "exit") == 0) Exit(command);
    else if (strcmp(cmd, "path") == 0) Path(command);
}