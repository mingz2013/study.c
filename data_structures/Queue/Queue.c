#include <stdio.h>
#include <stdlib.h>

// 预定义常量和类型
#define TRUE				1
#define FALSE				0
#define OK					1
#define ERROR				0
#define OVERFLOW			-2
typedef int Status;
typedef int QElemType;

// 单链队列，队列的链式存储结构
typedef struct QNode{
		QElemType		data;
		struct QNode	*next;
}QNode, *QueuePtr;
typedef struct{
	QueuePtr front;				// 队头指针
	QueuePtr rear;				// 队尾指针
}LinkQueue;

Status InitQueue(LinkQueue &Q){
	// 构造一个空队列Q
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)	exit(OVERFLOW);			// 存储空间分配失败
	Q.front->next = NULL;
	return OK;
}

Status DestroyQueue(LinkQueue &Q){
	// 销毁队列Q
	while(Q.front){
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e){
	// 插入元素e为Q的新的队尾元素
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)	exit(OVERFLOW);			// 存储空间分配失败
	p->data = e; p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e){
	// 若队列不空，则删除Q的队头元素，用e返回其值，并返回OK；后则返回ERROR
	if(Q.front == Q.rear)return ERROR;
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if(Q.rear == p)Q.rear == Q.front;
	free(p);
	return OK;
}

int main(){
	return 0;
}
