#include <stdio.h>

int max(int i, int j)
{
	if(i > j)
	{
		return i;
	}else{
		return j;
	}
}

int main()
{
	int i, j, k;
	i = 3;
	j = 5;
	printf("hello linux \n");
	k = max(i, j);
	printf("%d\n", k);
	return 0;
}
