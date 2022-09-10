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
struct sockaddr_in addr;
stud temp;

void createClientSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORTNO);
    connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
}

void performClientTask() {
    printf("Enter the name and the roll: ");
    scanf("%s %d", temp.name, &(temp.roll));
    printf("Sending...\n");
    write(sockfd, &temp, sizeof(temp));
    printf("Reading...\n");
    read(sockfd, &temp, sizeof(temp));
    printf("New Data: %s %d", temp.name, temp.roll);
}

int main() {
    createClientSocket();
    performClientTask();
    return 0;
}
