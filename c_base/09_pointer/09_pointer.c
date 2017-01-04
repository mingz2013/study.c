#include<stdio.h>
int main(){
	int i, j;
	int *p;
	char a, b;
	char *q;
	i=5;
	p = &i;
	j=*p;
	a='w';
	q=&a;
	b=*q;
	printf("%d  %d  %d \n", i, j, *p);
	printf("%c  %c  %c \n", a, b, *q);
	return 0;
}
