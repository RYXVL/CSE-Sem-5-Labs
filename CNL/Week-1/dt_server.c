#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include <time.h>

    int sockfd, newsockfd, portno, clilen, n = 1;
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    char buff[256];

void createServerSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(5410);
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
}

void performServerTask() {
    while(1) {
        printf("Server Waiting\n");
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
        n = read(newsockfd, buff, sizeof(buff));
        printf("Message from client: %s\n", buff);
        time_t t = time(NULL);
        printf("\n Current date and time is : %s", ctime(&t));
        // printf("%ld", sizeof(ctime(&t)));
        n = write(newsockfd, ctime(&t), sizeof(ctime(&t)));
    }
}

int main() {
    createServerSocket();
    performServerTask();
    return 0;
}