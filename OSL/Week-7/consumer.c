#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st {
    long int my_msg_type;
    int num;
};

int isPalindrome(int t) {
    int arr[100], n = 0;
    while(t >0) {
        int dig = t%10;
        t/=10;
        arr[n++] = dig;
    }
    for(int i = 0; i<n/2; i++)
        if(arr[i] != arr[n-i-1]) return 0;
    return 1;
}

int main() {
    int running = 1;
    int msgid;
    struct my_msg_st some_data;
    long int msg_to_receive = 0;
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid == -1) {
        perror("Message Get Failed");
        exit(0);
    }
    while (running) {
        if(msgrcv(msgid, (void *)&some_data, sizeof(msgid), msg_to_receive, 0) == -1) {
            perror("Message Receive Failed");
            exit(0);
        }
        if(some_data.num == -1) running = 0;
        else if(isPalindrome(some_data.num)) printf("%d is a palindrome\n", some_data.num);
        else printf("%d is not a palindrome\n", some_data.num);
    }
    if(msgctl(msgid, IPC_RMID, 0) == -1) {
        perror("Meessage Control Failed");
        exit(0);
    }
    exit(0);
}