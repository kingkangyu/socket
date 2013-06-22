//
//  main.cpp
//  serve2
//
//  Created by kangyu on 13-6-21.
//  Copyright (c) 2013年 kangyu. All rights reserved.
//

#include "iostream"
#include <sys/types.h>
#include <sys/socket.h>
#include "unistd.h"
#include <netinet/in.h>
#include <arpa/inet.h>

#define SA struct sockaddr
#define SAI struct sockaddr_in
#define SERV_PORT 19805
#define LENGTH 1
#define SIZE 120

int main(int argc, const char * argv[])
{

    int res;
    int sockfd;
    int clientfd;
    SAI hostaddr;
    SAI clientaddr;    
    ssize_t cnt;    
    socklen_t len;    
    char buf[SIZE];
    
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    
    if(sockfd==-1)
    {
        perror("套接字创建失败\n");
        exit(1);
    }
    memset(&hostaddr, 0, sizeof(hostaddr));
    
    hostaddr.sin_family=AF_INET;
    hostaddr.sin_port=htons(SERV_PORT);
    hostaddr.sin_addr.s_addr=INADDR_ANY;
    

    res = bind (sockfd,( SA *)&hostaddr, sizeof(hostaddr) );
    
    
    if(res==-1)
    {
        perror("绑定失败\n");
        exit(1);
    }
    
    res=listen(sockfd, LENGTH);
    
    if (res==-1) {
        perror("监听失败\n");
        exit(0);
    }
    
    printf("等待客户端请求连接\n");
    
    while (1) {
    
        len=sizeof(clientaddr);
        
        clientfd=accept(sockfd, (SA *)&clientaddr, &len);
        
        if (clientfd==-1) {
            perror("接受连接请求出错\n");
            continue;
        }
        printf("客户端IP:%s\n",inet_ntoa(clientaddr.sin_addr));
    
        cnt = recv (clientfd, buf, sizeof(buf), 0);
        
        if (cnt== -1) {
            perror("接收数据错误\n");
            exit(1);
        }
        printf("收到数据:%s\n",buf);
        close(clientfd);
    }
    
    return 0;
}

























