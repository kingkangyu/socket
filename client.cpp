//
//  main.cpp
//  client2
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
#define LENGTH 10
#define SIZE 120

int main(int argc, const char * argv[])
{
    int res;
    int sockfd;
    SAI servaddr;
    char buf[SIZE];
    ssize_t cnt;
    char tmp;
    
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd==-1) {
        perror("套接字创建失败\n");
        exit(1);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);    
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
       
    res=connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
    
    if (res==-1) {
        perror("连接失败\n");
        exit(1);
    }
    printf("连接成功\n输入参数：");
    scanf("%s",&tmp);
    strcpy(buf, &tmp);
    
    cnt=send(sockfd, buf, sizeof(buf), 0);
    
    if (cnt==-1) {
        perror("发送失败\n");
        exit(1);
    }
    printf("发送数据:%s\n",buf);
    close(sockfd);
    
    return 0;
}

























