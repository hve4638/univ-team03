#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wish.h>

static void runProgram(const char* FILE, int size_t)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        exit(1);
    } else if (pid == 0) {
        char *args[] = {"wish", NULL};  // 실행할 프로그램과 옵션 설정
        execvp("wish", args);  // wish 실행
        exit(0);
    } else {
        wait(NULL);
    }

    return 0;
}
