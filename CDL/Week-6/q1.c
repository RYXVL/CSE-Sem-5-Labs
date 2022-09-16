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
    if(str[ind]=='a' || str[ind]=='>') {
        ind++;
        return;
    }
    else if(str[ind]=='(') {
        ind++;
        T();
        if(str[ind]==')') {
            ind++;
            return;
        }
        else invalid();
    }
    else invalid();
}

void T() {
    S();
    TPrime();
}

void TPrime() {
    if(str[ind]==',') {
        ind++;
        S();
        TPrime();
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