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
#define LENGTH 10
#define SIZE 30

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
    int childpid;
    
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    
    if(sockfd==-1)
    {
        perror("socket create fail\n");
        exit(1);
    }
    memset(&hostaddr, 0, sizeof(hostaddr));
    
    hostaddr.sin_family=AF_INET;
    hostaddr.sin_port=htons(SERV_PORT);
    hostaddr.sin_addr.s_addr=INADDR_ANY;
    
    
    res = bind (sockfd,( SA *)&hostaddr, sizeof(hostaddr) );
    
    
    if(res==-1)
    {
        perror("bind fail\n");
        exit(1);
    }
    
    res=listen(sockfd, LENGTH);
    
    if (res==-1) {
        perror("listen fail\n");
        exit(0);
    }
    
    printf("wait for client\n");
    
    while (1) {
        
        len=sizeof(clientfd);
        
        clientfd=accept(sockfd, (SA *)&clientaddr, &len);
        if (clientfd!=-1) {
            printf("accept correct\n");
            printf("Client IP:%s\n",inet_ntoa(clientaddr.sin_addr));
        }
        else
        {
            continue;
        }
        
        if ( (childpid=fork()) ==0 )
        {
            while(1)
            {
                close(sockfd);
                cnt = recv (clientfd, buf, sizeof(buf), 0);
                printf("Client IP:%s\n",inet_ntoa(clientaddr.sin_addr));
                
                if (cnt==0) {
                    exit(0);
                }
            
                printf("recv data:%s\n",buf);
                if (strcmp(buf, "close")==0) {
                    printf("Client off\n");
                    exit(0);
                }
            }
            exit(0);
        }
        close(clientfd);
    }
    
    return 0;
}

























