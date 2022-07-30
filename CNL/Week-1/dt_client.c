#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include <time.h>

int len, result, sockfd, n = 1;
    struct sockaddr_in address;
    char ch[256], buff[2000];
    time_t t;

void createClientSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(5410);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr*)&address, len);
    if(result == -1) {
        perror("CLIENT ERROR\n");
        exit(1);
    }
}

void performClientTask() {
    printf("Enter the string: ");
    gets(ch);
    ch[strlen(ch)] = '\0';
    write(sockfd, ch, strlen(ch));
    printf("Time: ");
    while(n) {
        n = read(sockfd, &t, sizeof(t));
        // printf("%ld", sizeof(buff));
        // puts(buff);
        printf("\n Current date and time is : %s", ctime(&t));
    }
}

int main() {
    createClientSocket();
    performClientTask();
    return 0;
}