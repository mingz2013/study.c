#include <stdio.h>
int main()
{
	int i, j;
	int *p, *q, *temp;
	printf("please input the first number: \n");
	scanf("%d", &i);
	printf("please input the second number: \n");
	scanf("%d", &j);
	p = &i;
	q = &j;
	if(*p > *q){
		temp = p;
		p = q;
		q = temp;
	}
	printf("%d %d \n", *p, *q);
	return 0;
}
