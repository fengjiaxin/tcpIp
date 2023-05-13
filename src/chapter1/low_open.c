//
// Created by fengjiaxin on 2023/4/26.
// 写入

#include <stdio.h> // printf  fputs
#include <stdlib.h> // exit
#include <fcntl.h> // open函数
#include <unistd.h> // write函数 close函数

void error_handling(char* message);

int main(void ) {
    int fd;
    char buf[] = "let us go!\n";
    fd = open("./data.txt",O_CREAT | O_WRONLY |O_TRUNC);
    if (fd == -1) {
        error_handling("open() error!");
    }
    printf("file desc : %d\n", fd);
    if (write(fd, buf, sizeof(buf)) == -1) {
        error_handling("write() error");
    }
    close(fd);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}

