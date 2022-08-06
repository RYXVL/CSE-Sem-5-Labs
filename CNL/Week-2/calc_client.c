#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

# define PORTNO 5003

int len, result, sockfd, n = 1;
// int opd1, opd2, res;
// char opr;
struct sockaddr_in address;
// char ch[256], res[256];
int arr[3], res[1];

void createClientSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);
    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr*)&address, len);
    if(result == -1) {
        perror("CLIENT ERROR\n");
        exit(1);
    }
}

void performClientTask() {
    printf("Enter the operand1 operator(+0, -1, *2, /3) operand2: ");
    for(int i=0; i<3; i++)
    scanf("%d", &(arr[i]));
    // printf("%d %d %d", arr[0], arr[1], arr[2]);
    write(sockfd, arr, sizeof(arr));
        n = read(sockfd,res, sizeof(res));
        printf("Result is: %d", res[0]);
}

int main() {
    createClientSocket();
    performClientTask();
    return 0;
}