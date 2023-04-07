# 리다이렉션

예 : `ls -la /tmp > output`


# 병렬 명령

`cmd1 & cmd2 & cmd3`

cmd1, cmd2, cmd3 병렬로 실행

# 프로그램 오류

> char error_message[30] = "An error has occurred\n";
>
> write(STDERR_FILENO, error_message, strlen(error_message)); 