#include <stdio.h>
#include <stdlib.h>

// 预定义常量和类型
#define TRUE				1
#define FALSE				0
#define OK					1
#define ERROR				0
#define OVERFLOW			-2
typedef int Status;
typedef int SElemType;

// 栈的顺序存储
#define STACK_INIT_SIZE			100			// 存储空间初始分配量
#define STACKINCREMENT			10			// 存储空间分配增量
typedef struct {
		SElemType	*base;					// 在栈构造之前和销毁之后，base的值为NULL
		SElemType	*top;					// 栈顶指针
		int stacksize;						// 当前已分配的存储空间，以元素为单位
}SqStack;

Status InitStack (SqStack &S){
	// 构造一个空栈S
	S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base){printf("存储空间分配失败");exit(OVERFLOW);}	// 存储分配失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType &e){
	// 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
	if(S.top == S.base)  return ERROR;
	e = *(S.top - 1);
	return OK;
}

Status Push(SqStack &S, SElemType e){
	// 插入元素e为新的栈顶元素
	if(S.top - S.base >= S.stacksize){// 栈满，追加存储空间
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if(!S.base) exit(OVERFLOW);		// 存储分配失败
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, SElemType &e){
	// 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
	if(S.top == S.base)return ERROR;
	e = * --S.top;
	return OK;
}

int main(){
	return 0;
}
