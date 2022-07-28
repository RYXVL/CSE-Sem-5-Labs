#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main() {
	int a = 10;
	float b = 5.396;
	char c = 'R';
	char str[] = "Ryan Sojan";
	printf("a = %d, b = %f, c = %c, str = %s, Hexadecimal for a = %x\n",a,b,c,str,a);
	errno = EPERM;
	printf("Error Access Number : %m\n");
}