#include<stdio.h>
int main()
{
	int i, j;
    char m;
	printf("please enter a char:\n");
	scanf("%c", &m);
	printf("the char is %c.\n", m);
	printf("please enter a number:\n");
	scanf("%d", &i);
	printf("please enter another number:\n");
	scanf("%d", &j);
	printf("%d + %d = %d \n", i, j, i+j);

	return 0;
}
