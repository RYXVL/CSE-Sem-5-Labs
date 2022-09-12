#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORTNO 5005

struct student {
    char name[20];
    int roll;
};
typedef struct student stud;

int sockfd, newsockfd;
struct sockaddr_in saddr, caddr;
stud temp;

void createServerSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
    listen(sockfd, 5);
}

void performServerTask() {
    printf("Server Starting...\n");
    int len = sizeof(caddr);
    newsockfd = accept(sockfd, (struct sockaddr*)&caddr, &len);
    if(fork()==0) {
        read(newsockfd, &temp, sizeof(temp));
        printf("Data Rec: %s %d", temp.name, temp.roll);
        int i = 0;
        while(temp.name[i]!='\0') i++;
        temp.name[i] = '2';
        temp.name[i+1] = '\0';
        temp.roll*=2;
        write(newsockfd, &temp, sizeof(temp));
        printf("Modified Data: %s %d", temp.name, temp.roll);
    }
    else close(newsockfd);
    
}

int main() {
    createServerSocket();
    performServerTask();
    return 0;
}
