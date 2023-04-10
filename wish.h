#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 두 메크로는 사용하지 않음
#define CMD char*
#define CMDArray char**

typedef struct {
/*
    cmd : 명령어 (경로가 포함되지 않는다)
    args : 인자
    argc : 인자 개수
    redriectTo : 출력할 파일, NULL이면 표준출력
*/
    const char* cmd;
    const char** args;
    size_t argc;
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


typedef struct CommandNode CommandNode;
// 이해안되면 LinkedList 찾아보기
struct CommandNode {
    Command* command;
    CommandNode* next; //다음 노드가 없다면 NULL
};

/*
    명령 실행시 찾는 위치
    char*의 배열이라 생각하면 됨
    배열처럼 순차로 돌면서 시작값이 0(NULL)이면 배열의 끝을 의미
    wishPATH 내에 저장되는 포맷은 '/bin', '/usr/bin' 같은 식으로 저장됨. 끝에 '/'가 붙어있지 않음
*/
extern const char** wishPATH;
extern size_t wishPATHCount;
/*
    사용 예시:
        int index = 0;
        while(wishPATH[index] != '\0') {
            printf("%s\n", wishPATH[index]);
            index++;
        }
        //wishPATH에 저장된 경로 출력

    또는:
        const char** p = wishPATH;
        while(*p != '\0') {
            printf("%s\n", *p);
            p++;
        }
        //첫번째 예제와 동일한 동작
    
    언제나 배열의 끝에 NULL이 있으므로 메모리를 벗어날 걱정은 안해도 된다
*/


/*
    CommandNode에서 Command를 찾아서 실행
    Command가 1개일수도 있고 여러개일수 있음
    여러개라면 병렬적으로 실행 (각각 다른 프로세스에서)

    isBuiltInCommand()로 내장명령인지 체크, 내장명령이라면 runBuiltInCommand 호출
    내장명령이 아닌 명령의 경우 wishPATH내에 존재하는 경로에서 프로그램을 찾는다.
    wishPATH 내에 해당 경로가 존재하지 않는 것까지 고려해서 찾는 코드를 작성
    아마 파일의 존재만 확인하는 것이 아니라 실행권한이 있는지도 체크해야 할듯?

    명령을 실행시 Command 구조체의 redirectTo이 NULL이 아니라면 출력을 표준출력 대신 파일출력으로 바꿔야 한다
    이거 원리가 pre-class에 나왔었던것 같음
*/
void runCommand(CommandNode*);

// 인자로 받은 Command가 내장명령이면 1, 아니면 0 리턴
int isBuiltInCommand(Command*);
// 내장 명령 실행, 적절한 내장 명령이 아니라면 아무 행동도 하지 않음
void runBuiltInCommand(Command*);


size_t splitCommand(char*, char***);
CommandNode* parseCommand(char**, size_t);
void freeCommandNode(CommandNode*);

void wish(FILE*);
void Error();