#include <stdio.h>
#include <stdlib.h>

// 预定义常量和类型
#define TRUE				1
#define FALSE				0
#define OK					1
#define ERROR				0
#define OVERFLOW			-2
typedef int Status;


// 串的定长顺序存储表示
#define MAXSTRLEN	255	// 用户可在255以内定义最大串长
typedef unsigned char SString[MAXSTRLEN + 1];		// 0号单元存放串的长度

Status Concat(SString &T, SString S1, SString S2){
	// 用T返回由S1和S2联接而成的新串。若未截断，则返回TRUE，否则返回FALSE
	bool uncut;
	if(S1[0] + S2[0] <= MAXSTRLEN){					// 未截断
		T[1..S1[0]] = S1[1..S1[0]];
		T[S1[0] + 1..S1[0] + S2[0]] = S2[1..S2[0]];
		T[0] = S1[0] + S2[0];	uncut = TRUE;
	}else if(S1[0] < MAXSTRLEN){					// 截断
		T[1..S1[0]] = S1[1..S1[0]];
		T[S1[0] + 1..MAXSTRLEN] = S2[1..MAXSTRLEN - S1[0]];
		T[0] = MAXSTRLEN; uncut = FALSE;
	}else{											// 截断，仅取S1
		T[0..MAXSTRLEN] =  S1[0..MAXSTRLEN];	// T[0] == S1[0] == MAXSTRLEN
		uncut = FALSE;
	}
	return uncut;
}

Status SubString(SString &Sub, SString S, int pos, int len){
	// Sub返回串S的第pos个字符起长度为len的子串
	// 其中，1 <= pos <= StrLength(S) 且 0 <= len <= StrLength(S) - pos + 1
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1) return ERROR;
	Sub[1..len] = S[pos..pos + len - 1];
	Sub[0] = len;
	return OK;
}

int main(){
	return 0;
}
