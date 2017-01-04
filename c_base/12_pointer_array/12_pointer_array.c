#include<stdio.h>
int main()
{
	int i;
	int *p;
	int a[10];
	for(i = 0; i < 10; i++){
		a[i] = i + 10;
	}
	p = a;
	for(i = 0; i < 10; i++){
		printf("%d ", *p);
		p++;
	}
	printf("\n");
	p=p-4;
	printf("%d ", *p);
	p=p-3;
	printf("%d ", *p);
	p=p+5;
	printf("%d ", *p);
	printf("\n");
	return 0;
}
