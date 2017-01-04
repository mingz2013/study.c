 # include <stdio.h>
int main()
{
	char a[100];
	int i;
	i = 0;
	printf("please input a string: \n");
	scanf("%s", a);
	while(a[i] != NULL){
		if(a[i] <= 122 && a[i] >= 97){
			a[i] = a[i] - 32;
		}
		i++;
	}
	printf("result: %s \n", a);
	return 0;
}
