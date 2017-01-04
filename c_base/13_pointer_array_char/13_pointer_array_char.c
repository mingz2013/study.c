#include<stdio.h>
int main()
{
	char a[30];
	char *p;
	int i;
	printf("please input a string: \n");
	scanf("%s", a);
	printf("result:\n");
	printf("%s\n", a);
	i = 0;
	while(a[i] != NULL){
		printf("%c", a[i]);
		i++;
	}
	printf("\n");
	p = a;
	printf("%s\n", p);
	while(*p != NULL){
		printf("%c", *p);
		p++;
	}
	printf("\n");
	return 0;
}
