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
    if(str[ind]=='a') {
        ind++;
        A();
        if(str[ind]=='c') {
            ind++;
            B();
            if(str[ind]=='e') {
                ind++;
                return;
            }
            else invalid();
        }
        else invalid();
    }
    else invalid();
}

void A() {
    if(str[ind]=='b') {
        ind++;
        APrime();
    }
    else invalid();
}

void APrime() {
    if(str[ind]=='b') {
        ind++;
        APrime();
    }
}

void B() {
    if (str[ind]=='d') ind++;
    else invalid();
}

int main() {
    printf("Enter the string: ");
    scanf("%s", str);
    S();
    if(str[ind]=='$') printf("SUCCESS");
    else printf("FAILURE - %c", str[ind]);
    return 0;
}