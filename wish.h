#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 두 메크로는 사용하지 않음
#define CMD char*
#define CMDArray char**

typedef struct {
    const char* cmd;
    const char** args;
    size_t argc;
    const char* redirectTo;
    const char* errRedirectTo;
} Command;

typedef struct CommandNode CommandNode;
struct CommandNode {
    Command* command;
    CommandNode* next; //다음 노드가 없다면 NULL
};

extern const char** wishPATH;
extern size_t wishPATHCount;
void runCommand(CommandNode*);

int isBuiltInCommand(Command*);
void runBuiltInCommand(Command*);

size_t splitCommand(char*, char***);
CommandNode* parseCommand(char**, size_t);
void freeCommandNode(CommandNode*);

void clearWishPATH();
void wish(FILE*);
void Error();