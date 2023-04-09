#include <unistd.h>
#include <sys/wait.h>
#include "wish.h"

void runCommand(CommandNode* commands) {
    pid_t pid;
    int status;
    while (commands != NULL) {
        Command* cmd = commands->command;

        if (isBuiltInCommand(cmd)) { // 내장 프로그램일 경우
            runBuiltInCommand(cmd);
        } else { // 외부 프로그램일 경우
            const char** p = wishPATH;

            while (*p != '\0') {
                if (access(p, X_OK) == 0) { //X_OK: 파일의 실행 권한 여부를 확인
                    break;
                }
                p++;
            }

            if (p == NULL) { //경로에서 명령어를 찾지 못했을 경우
                fprintf(stderr, "wish: %s: command not found\n", cmd->cmd);
                commands = commands->next;
                continue;
            }

            pid = fork();

            if (pid == 0) {
                // 자식프로세서
                if (cmd->redirectTo != NULL) {
                    FILE* outFile = fopen(cmd->redirectTo, "w");
                    if (outFile == NULL) { //파일 열기 실패
                        exit(1);
                    }
                    dup2(fileno(outFile), STDOUT_FILENO); // 이후의 printf와 같은 출력은 모두 outFile에 저장
                }

                execv(p, (char* const*) cmd->args); // args의 마지막은 NULL로 끝나야함
                perror("execv failed");
                exit(1);
            } else if (pid < 0) { //fork() 호출 실패할 경우
                exit(1);
            }
            // 부모 프로세서
            if (waitpid(pid, &status, 0) == -1) { 
                exit(1);
            }
        }

        commands = commands->next;
    }
}