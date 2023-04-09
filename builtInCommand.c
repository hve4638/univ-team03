#include "wish.h"

static void CD(Command* command) {
    
}

static void Path(Command* command) {
    
}

static void Exit(Command* command) {
    
}

int isBuiltInCommand(Command* command) {
    return 0;

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
    //미구현
}