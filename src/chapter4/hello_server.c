//
// Created by fengjiaxin on 2023/4/26.
//

#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h> // memset
#include <unistd.h>
#include <arpa/inet.h> // sockaddr_in socklen_t
#include <sys/socket.h> // socket bind listen

void error_handling(char* message);

int main(int argc, char* argv[]) {
    int serv_sock;
    int clnt_sock;

//    struct sockaddr_in {
//        __uint8_t       sin_len;
//        sa_family_t     sin_family; 协议族
//        in_port_t       sin_port; 16位端口号
//        struct  in_addr sin_addr; // 32位IP地址
//        char            sin_zero[8]; // 不使用
//    };


//    struct sockaddr {
//        __uint8_t       sa_len;
//        sa_family_t     sa_family;      地址族
//        char            sa_data[14];    地址信息，包括ip地址和端口号
//    };
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t  clnt_addr_size;

    char message[] = "hello world !";
    if (argc != 2) {
        printf("usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    /**
     * 字节序转换，网络字节序统一为大端序
     * htons : h表示主机字节序， n表示网络字节序， s指short, l指long
     */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 利用常数分配服务器IP地址
    serv_addr.sin_port= htons(atoi(argv[1]));

    if (bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }
    // 服务器端套接字， 连接请求队列长度

    // 进入等待连接请求状态
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);

    // 受理客户端连接请求
    clnt_sock= accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1) {
        error_handling("accept() error");
    }
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}