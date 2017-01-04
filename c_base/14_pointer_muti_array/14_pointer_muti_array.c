#include<stdio.h>
int main()
{
	int i = 10, m, n;
	int a[4][5];
	int *p;
	for(m = 0; m < 4; m++){
		for(n = 0; n < 5; n++){
			a[m][n] = i;
			i++;
		}
	}
	p = a;
	for(m = 0; m < 4; m++){
		for(n = 0; n < 5; n++){
			printf("a[%d][%d]=%d ", m, n, *(p + (5 * m) + n));
		}

		printf("\n");
	}
	return 0;
}
