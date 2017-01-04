#include<stdio.h>
int main()
{
	char a[100];
	char c = 'a';
	int i = 0;
	while(1){
		scanf("%c", &c);
		if(c == '#'){
			break;
		}
		a[i] = c;
		i++;
	}
	i = 0;
	while(a[i] != NULL){
		printf("%c", a[i]);
		i++;
	}
    printf("\n");

	return 0;
}
