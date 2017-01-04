#include <stdio.h>
#include <stdlib.h>

// 预定义常量和类型
#define TRUE				1
#define FALSE				0
#define OK					1
#define ERROR				0
#define OVERFLOW			-2
typedef int Status;
typedef int ElemType;

// 线性列表的单链表存储结构
typedef struct LNode{
		ElemType 		data;
		struct LNode	*next;
}LNode, *LinkList;

Status GetElem_L(LinkList L, int i, ElemType &e){
	// L为带头节点的单链表的头指针
	// 当第i个元素存在时，其值付给e并返回OK，否则返回ERROR
	LinkList p = L->next; int j = 1;	// 初始化，p指向第一个节点，j为计数器
	while(p && j < i){					// 顺时针向后查找，直到p指向第i个元素或者p为空
		p = p->next; ++j;
	}
	if(!p || j > i) return ERROR;		// 第i个元素不存在
	e = p->data;						// 取第i个元素
	return OK;
}

Status ListInsert__L(LinkList &L, int i, ElemType e){
	// 在带头节点的单链线性表L中第i各位值之前插入元素e
	LinkList p = L; int j = 0;
	while(p && j < i - 1){							// 寻找第i-1个节点
		p = p->next; ++j;
	}
	if(!p || j > i - 1) return ERROR;				// i小于1或者大于表长+1
	LinkList s = (LinkList)malloc(sizeof(LNode));	// 生成新节点
	s->data = e; s->next = p->next;					// 插入L中
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList &L, int i, ElemType &e){
	// 在带头节点的单链表L中，删除第i个元素，并由e返回其值
	LinkList p = L;int j = 0;
	while(p->next && j < i - 1){				// 寻找第i个节点，并令p指向其前趋
		p = p->next; ++j;
	}
	if(!(p->next) || j > i - 1) return ERROR;	// 删除位置不合里
	LinkList q = p->next; p->next = q->next;	// 删除并释放节点
	e = q->data; free(q);
	return OK;
}

Status CreateList_L(LinkList &L, int n){
	// 逆位序输入n个值，建立带表头节点的单链线性表L
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;								// 先建立一个带头节点的单链表
	int i;
	for(i = n; i > 0; --i){
		LinkList p = (LinkList)malloc(sizeof(LNode));	// 生成新节点
		scanf("%d", &p->data);						// 输入元素值
		p->next = L->next; L->next = p;			// 插入到表头
	}
}

void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc){
	// 已知单链线性表La和Lb的元素按值非递减排列
	// 归并La和Lb得到新的单链线性表Lc， Lc的元素也按值非递减排列
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc;
	Lc = pc = pa;								// 用La的头节点作为Lc的头节点
	while(pa && pb){
		if(pa->data <= pb->data){
			pc->next = pa; pc = pa; pa = pa->next;
		}else{
			pc->next = pb; pc = pb; pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;					// 插入剩余段
	free(Lb);									// 释放Lb的头节点
}

int main(){
	LinkList L;
	ElemType e;
	return 0;
}
