#include<stdio.h>
int main()
{
	int a[10];
	int i;
	for(i = 0; i <= 9; i++){
		a[i] = i+10;
	}
	for(i=0; i<=9;i++){
		printf("%d ", a[i]);
	}
    printf("\n");
	return 0;
}
