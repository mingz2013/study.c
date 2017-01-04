#include <stdio.h>

void byteorder()
{// 用于检查机器的字节序
	union
	{
		short value;
		char union_bytes[ sizeof( short ) ];
	} test;
	
	test.value = 0x0102;
	
	if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
	{
		printf("big endian\n");
	}
	else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1))
	{
		printf("little endian\n");
	}
	else
	{
		printf("unknown...\n");
	}
	//	printf("%d\n", sizeof(test.union_bytes));
}

int main(void)
{
	byteorder();
	return 0;
}

