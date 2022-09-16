#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[100];
int ind = 0;

void invalid() {
    printf("FAILED");
    exit(0);
}

void S() {
    if(str[ind]=='(') {
        ind++;
        L();
        if(str[ind]==')') {
            ind++;
            return;
        }
        else invalid();
    }
    else if(str[ind]=='a') {
        ind++;
        return;
    }
    else invalid();
}

void L() {
    S();
    LPrime();
}

void LPrime() {
    if(str[ind]==',') {
        ind++;
        S();
        LPrime();
    }
}

int main() {
    printf("Enter the string: ");
    scanf("%s", str);
    S();
    if(str[ind]=='$') printf("SUCCESS");
    else printf("FAILURE - %c", str[ind]);
    return 0;
}