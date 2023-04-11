#include <unistd.h>
#include <sys/wait.h>
#include "wish.h"

static char* argv[1024];

static char** makeArgv(char* path, Command* command) {
    size_t argc = command->argc;
    argv[0] = (char*)command->cmd;
    for(size_t i=0; i < argc; i++) {
        argv[i+1] = (char*)command->args[i];
    }
    argv[argc+1] = NULL;
    return argv;
}

void runCommand(CommandNode *commands)
{
    pid_t pid;
    int status;
    while (commands != NULL) {
        Command *cmd = commands->command;

        if (isBuiltInCommand(cmd)) {
            runBuiltInCommand(cmd);
        }
        else { // 외부 프로그램일 경우
            const char **p = wishPATH;
            char path[4096];
            
            while (*p != NULL) {
                snprintf(path, sizeof(path), "%s/%s", *p, cmd->cmd);
                if (access(path, X_OK) == 0) {   // 디렉토리의 실행 권한 여부를 확인
                    break;
                }
                p++;
            }

            if (*p == NULL) { // 경로에서 명령어를 찾지 못했을 경우
                Error();
                commands = commands->next;
                continue;
            }

            char** argv = makeArgv(path, cmd);
            pid = fork();
            if (pid == 0) {
                // 자식프로세서
                if (cmd->redirectTo != NULL) {
                    FILE *outFile = fopen(cmd->redirectTo, "w");
                    if (outFile == NULL) { // 파일 열기 실패
                        Error();
                        exit(1);
                    }
                    dup2(fileno(outFile), STDOUT_FILENO); // 이후의 printf와 같은 출력은 모두 outFile에 저장
                }
                if (cmd->errRedirectTo != NULL) {
                    FILE *errFile = fopen(cmd->errRedirectTo, "w");
                    if (errFile == NULL) { // 파일 열기 실패
                        Error();
                        exit(1);
                    }
                    dup2(fileno(errFile), STDERR_FILENO);
                }

                execv(path, (char *const *)argv); // args의 마지막은 NULL로 끝나야함
                perror("execv failed");
                exit(1);
            }
            else if (pid < 0) { // fork() 호출 실패할 경우
                Error();
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