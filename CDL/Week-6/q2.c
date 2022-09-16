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
    U();
    V();
    W();
}

void U() {
    if(str[ind]=='(') {
        ind++;
        S();
        if(str[ind]==')') {
            ind++;
            return;
        }
        else invalid();
    }
    else if(str[ind]=='a') {
        ind++;
        S();
        if(str[ind]=='b') {
            ind++;
            return;
        }
        else invalid();
    }
    else if(str[ind]=='d') {
        ind++;
        return;
    }
    else invalid();
}

void V() {
    if(str[ind]=='a') {
        ind++;
        V();
    }
}

void W() {
    if (str[ind]=='c') {
        ind++;
        W();
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