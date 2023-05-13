//
// Created by fengjiaxin on 2023/4/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[]) {
    int sock;
    char message[BUF_SIZE];
    struct sockaddr_in serv_addr;
    int str_len;
    if (argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handling("socket() error");
    }

    //inet_addr， 将字符串形式的ip地址转化为32位整数型数据(大端序)
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port= htons(atoi(argv[2]));
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    } else {
        puts("connected.......");
    }

    while (1) {
        fputs("Input message(Q to quit): ",stdout);
        fgets(message,BUF_SIZE, stdin);
        if (!strcmp(message,"q\n") || !strcmp(message,"Q\n") )
            break;
        write(sock, message, strlen(message));
        str_len = read(sock, message,BUF_SIZE - 1);
        message[str_len] = 0;
        printf("Message from server : %s", message);
    }
    close(sock);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}