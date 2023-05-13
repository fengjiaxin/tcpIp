//
// Created by fengjiaxin on 2023/4/26.
//


#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h> // memset
#include <unistd.h>
#include <arpa/inet.h> // sockaddr_in socklen_t
#include <sys/socket.h> // socket bind listen
#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc, char* argv[]) {
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t  clnt_addr_size;

    if (argc != 2) {
        printf("usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }


    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 利用常数分配服务器IP地址
    serv_addr.sin_port= htons(atoi(argv[1]));

    if (bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    while (1) { // 无限循环
        clnt_addr_size = sizeof(clnt_addr);
        str_len = recvfrom(serv_sock,message,BUF_SIZE, 0,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
        sendto(serv_sock,message,str_len, 0,(struct sockaddr*)&clnt_addr, clnt_addr_size);
    }
    close(serv_sock);
    return 0;

}

void error_handling(char* message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}