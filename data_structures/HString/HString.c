#include <stdio.h>
#include <stdlib.h>

// 预定义常量和类型
#define TRUE				1
#define FALSE				0
#define OK					1
#define ERROR				0
#define OVERFLOW			-2
typedef int Status;

// 串的堆分配存储表示

typedef struct{
	char * ch;				// 若是非空串，则按串长分配存储区，否则ch为null
	int length;				// 串长度
}HString;

Status StrInsert(HString &S, int pos, HString T){
	// 1 <= pos <= StrLength(S) + 1. 在串S的第pos个字符之前插入串T。
	if(pos < 1 || pos > S.length + 1) return ERROR;			// pos不合发
	if(T.length){						// T非空，则重新分配区间，插入T
		if(! (S.ch = (char*)realloc(S.ch, (S.length + T.length) * sizeof(char)) ))	exit(OVERFLOW);
		for(i = S.length - 1; i >= pos - 1; --i)		// 为插入T而腾出位置
			S.ch[i + T.length] = S.ch[i];
		S.ch[pos - 1..pos + T.length - 2] = T.ch[0..T.length - 1];	// 插入T
		S.length += T.length;
	}
	return OK;
}

Status StrAssign(HString &T, char * chars){
	// 生成一个其值等于串常量chars的串T
	if(T.ch) free(T.ch);			// 释放T原有空间
	for(i = 0, c = chars; c; ++i, ++c);	// 求chars的长度i
	if(!i){T.ch = NULL; T.length = 0;}
	else{
		if(!(T.ch = (char*)malloc(i * sizeof(char))))	exit(OVERFLOW);
		T.ch[0..i - 1] = chars[0..i - 1];
		T.length = i;
	}
	return OK;
}

int StrLength(HString S){
	// 返回S的元素个数，称为串的长度
	return S.length;
}

int StrCompare(HString S, HString T){
	// 若S》T，则返回值》0，若S=T，则返回值=0，若S《T，则返回值《0
	for(i = 0; i < S.length && i < T.length; ++i)
		if(S.ch[i] != T.ch[i])	return S.ch[i] - T.ch[i];
	return S.length - T.length;
}

Status ClearString(HString &S){
	// 将S清为空串
	if(S.ch){free(S.ch); S.ch = NULL;}
	S.length = 0;
	return OK;
}

Status Concat(HString &T, HString S1, HString S2){
	// 用T返回由S1和S2联接而成的新串
	if(T.ch) free(T.ch);		// 释放旧空间
	if(!(T.ch = (char*)malloc(S1.length + S2.length) * sizeof(char)))	exit(OVERFLOW);
	T.ch[0..S1.length - 1] = S1.ch[0..length - 1];
	T.length = S1.length + S2.length;
	T.ch[S1.length..T.length - 1] = S2.ch[0..S2.length - 1];
	return OK;
}

Status SubString(HString &Sub, HString S, int pos, int len){
	// 用Sub返回串S的第pos个字符起长度为len的子串
	// 其中，1 《= pos <= StrLength(S) 且 0 <= len <= StrLength(S) - pos + 1
	if(pos < 1  || pos > S.length || len < 0 || len > S.length - pos + 1)	return ERROR;
	if(Sub.ch) free(Sub.ch);		// 释放空间
	if(!len){Sub.ch = NULL; Sub.length = 0;}		// 空子串
	else{											// 完整子串
		Sub.ch = (char *)malloc(len * sizeof(char));
		Sub.ch[0..len - 1] = S.ch[pos - 1..pos + len - 2];
		Sub.length = len;
	}
	return OK;
}

