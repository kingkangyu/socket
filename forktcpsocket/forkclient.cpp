//
//  main.cpp
//  client2
//
//  Created by kangyu on 13-6-21.
//  Copyright (c) 2013年 kangyu. All rights reserved.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "iostream"
#include <sys/types.h>
#include <sys/socket.h>
#include "unistd.h"
#include <netinet/in.h>
#include <arpa/inet.h>


#define SA struct sockaddr
#define SAI struct sockaddr_in
#define SERV_PORT 19805
#define IP "10.211.55.2"
#define IPT "127.0.0.1"
#define LENGTH 10
#define SIZE 30

int main(int argc, const char * argv[])
{
    int res;
    int sockfd;
    SAI servaddr;
    char buf[SIZE];
    ssize_t cnt;
    char tmp[30];
    
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd==-1) {
        perror("socket creat fail\n");
        exit(1);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);    
    servaddr.sin_addr.s_addr = inet_addr(IP);
       
    res=connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
    
    if (res==-1) {
        perror("connect fail\n");
        exit(1);
    }
    while (1) {
        printf("linked the serve\ninput:");
        scanf("%s",tmp);
        strcpy(buf, tmp);
        if(strcmp(tmp,"close")==0)
        {
            cnt=send(sockfd, buf, sizeof(buf), 0);
            printf("send data:%s\nclient close\n",buf);
            close(sockfd);
            exit (0);
        }
        
        cnt=send(sockfd, buf, sizeof(buf), 0);
        
        printf("send data:%s\n",buf);
        
    }
    close(sockfd);
    
    return 0;
}

























