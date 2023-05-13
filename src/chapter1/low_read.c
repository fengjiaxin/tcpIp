//
// Created by fengjiaxin on 2023/4/26.
// 从文件中读取
#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <fcntl.h> // open
#include <unistd.h> // read close
#define BUF_SIZE 100

void error_handling(char* message);

int main(void) {
    int fd;
    char buf[BUF_SIZE];
    fd = open("./data.txt", O_RDONLY);
    if (fd == -1) {
        error_handling("open() error");
    }
    printf("file desc : %d\n",fd);
    if (read(fd, buf, sizeof(buf)) == -1) {
        error_handling("read error");
    }
    printf("file data : %s", buf);
    close(fd);

    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}

