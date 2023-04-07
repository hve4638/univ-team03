#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CMD char*
#define CMDArray char**

typedef struct {
    // cmd : 경로를 포함한 명령어
    // args : 인자
    // argc : 인자 개수
    // redriectTo : 출력할 파일, NULL이면 표준출력
    const char* cmd;
    const char** args;
    const size_t argc;
    const char* redirectTo;
} Command;
/* 프롬프트에 'ls > file.txt' 가 입력되면
    Command cmd;
    cmd.cmd = "ls";
    cmd.argv = NULL;
    cmd.argc = 0;
    cmd.redirectTo = "file.txt";
    로 처리됨
*/

// 이해안되면 LinkedList 찾아보기
typedef struct CommandNode {
    Command* command;
    CommandNode* next; //다음 노드가 없다면 NULL
} CommandNode;

/*
    CommandNode에서 Command를 찾아서 실행
    Command가 1개일수도 있고 여러개일수 있음
    여러개라면 병렬적으로 실행 (각각 다른 프로세스에서)
*/
void runCommand(CommandNode*);


void runBuiltInCommand(Command*);

size_t splitCommand(char*, char***);
CommandNode* parseCommand(char**, size_t, size_t*);

void error();