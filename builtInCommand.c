#include "wish.h"

static void CD(Command* command) {
    if (command->argc == 0 || command->argc > 1) {
        Error();
    }
    else if (chdir(command->args[0]) == -1) {
        Error();
    }
}

static void Path(Command* command) {
    printf("Not Implement\n");


    //wishPATHCount++;
}

static void Exit(Command* command) {
    if (command->argc == 0) {
        exit(0);
    }
    else {
        Error();
    }
}

int isBuiltInCommand(Command* command) {
    const char* cmd = command->cmd;

    if (strcmp(cmd, "cd") == 0) {
        return 1;
    } else if (strcmp(cmd, "exit") == 0) {
        return 1;
    } else if (strcmp(cmd, "path") == 0) {
        return 1;
    } else {
        return 0;
    }
}

void runBuiltInCommand(Command* command) {
    const char* cmd = command->cmd;
    if (strcmp(cmd, "cd") == 0) {
        CD(command);
    } else if (strcmp(cmd, "exit") == 0) {
        Exit(command);
    } else if (strcmp(cmd, "path") == 0) {
        Path(command);
    } else {
        return;
    }
}