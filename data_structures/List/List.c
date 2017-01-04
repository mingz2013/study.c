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

// 线性表的动态分配顺序存储结构
#define LIST_INIT_SIZE		100	// 线性表存储空间的初始化分配量
#define LISTINCREMENT		10	// 线性表存储空间的分配增量

typedef struct{
		ElemType	*elem;		// 存储空间基址
		int			length;		// 当前长度
		int			listsize;	// 当前分配的存储容量（以sizeof(ElemType为单位）
}SqList;


Status InitList_Sq(SqList &L){
	// 线性表初始化
		L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
		if(! L.elem) {puts("InitList_Sq malloc false"); exit(OVERFLOW);}	// 存储分配失败
		L.length = 0;					// 空表长度为0
		L.listsize = LIST_INIT_SIZE;	// 初始存储空量
		return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e){
	// 在顺序线性表L中第i个位置之前插入新的元素 e
		// i 的合法值为 1<= i <=ListLength_Sq(L) + 1
		if(i < 1 || i > L.length + 1) {puts("ListInsert_Sq i value is not allow"); return ERROR;}		// i 值不合法
		if(L.length >= L.listsize){						// 当前存储空间已满，增加分配
			ElemType* newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType) );
			if(! newbase) {puts("ListInsert_Sq malloc false"); exit(OVERFLOW);}			// 存储空间分配失败
			L.elem = newbase;							// 新基址
			L.listsize += LISTINCREMENT;				// 增加存储容量
		}
		ElemType* q = &(L.elem[i - 1]);							// q为插入位置
		ElemType* p;
		for(p = &(L.elem[L.length - 1]); p>= q; --p){
			*(p+1) = *p;								// 插入位置及之后的元素右移
		}
		*q = e;											// 插入e
		++L.length;										// 表长 增1
		return OK;
}

Status ListDelete_Sq(SqList &L, int i, ElemType &e){
	// 在顺序线性表L中删除第i个元素，并用e返回其值
		// i的合法值为 1 <= i <= ListLength_Sq(L)
		if(i < 1 || i > L.length) {puts("ListDelete_Sq i value is not allow"); return ERROR;}		// i 值不合法
		ElemType *p = &(L.elem[i -1]);				// p为被删除元素的位置
		e = *p;										// 被删除元素的值付给e
		ElemType* q = L.elem + L.length - 1;		// 表尾元素的位置
		for(++p; p <= q; ++p)	*(p -1) = *p;		// 被删除元素之后的元素左移
		--L.length;									// 表长 减1
		return OK;
		
}

Status compare(ElemType e1, ElemType e2){
	return e1 == e2;
}

int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType)){
	// 在顺序线性表L中查找第一个值与e满足compare()的元素的位序
	// 若找到，则返回其在L中的位序，后则返回0
	int i = 1;						// i的初始值为第一个元素的位序
	ElemType* p = L.elem;			// p的初始值为第一个元素的存储位置
	while(i <= L.length && !(*compare)(*p++, e)) ++i;
	if(i <= L.length) return i;
	else return 0;
}

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc){
	// 已知顺序线性表La和Lb的元素按值非递减排列
	// 归并La 和Lb得到新的顺序线性表Lc， Lc的元素也按值非递减排列
	ElemType* pa = La.elem;
	ElemType* pb = La.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	ElemType* pc = Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
	if(!Lc.elem) {puts("MergeList_Sq malloc false"); exit(OVERFLOW);}			// 存储空间分配失败
	ElemType* pa_last = La.elem + La.length - 1;
	ElemType* pb_last = Lb.elem + Lb.length - 1;
	while(pa <= pa_last && pb <= pb_last){					// 合并
			if(*pa <= *pb) *pc++ = *pa++;
			else *pc++ = *pb++;
	}
	while(pa <= pa_last) *pc++ = *pa++;						// 插入La剩余元素
	while(pb <= pb_last) *pc++ = *pb++;						// 插入Lb的剩余元素
}

int main(){
		SqList L;
		InitList_Sq(L);
		printf("InitList length : %d\n",  L.length);
		printf("InitList listsize : %d\n",  L.listsize);
		ListInsert_Sq(L, 1, 4);
		ListInsert_Sq(L, 1, 3);
		ListInsert_Sq(L, 1, 2);
		ListInsert_Sq(L, 1, 1);
		int i;
		ListDelete_Sq(L, 1, i);
		printf(" del int is %d\n", i);
		i = LocateElem_Sq(L, 3, (*compare));
		printf("3 is in %d\n", i);
		SqList L2;
		InitList_Sq(L2);
		ListInsert_Sq(L2, 1, 4);
		ListInsert_Sq(L2, 1, 3);
		ListInsert_Sq(L2, 1, 2);
		ListInsert_Sq(L2, 1, 1);
		i = LocateElem_Sq(L2, 4, (*compare));
		printf("4 is in %d\n", i);
		SqList L3;
		InitList_Sq(L3);
		MergeList_Sq(L, L2, L3);
		i = LocateElem_Sq(L3, 3, (*compare));
		printf("3 is in %d\n", i);
		return OK;
}
