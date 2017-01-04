//
// Created by zhaojm on 01/01/2017.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int MyRecv(int iSock, char *pchBuf, size_t tCount) {
	size_t tBytesRead = 0;
	int iThisRead;
	while (tBytesRead < tCount) {
		do {
			iThisRead = read(iSock, pchBuf, tCount - tBytesRead);
		} while ((iThisRead < 0) && (errno == EINTR));
		if (iThisRead < 0) { // 说明error了
			return (iThisRead);
		} else if (iThisRead == 0) { // 说明读完了
			return (tBytesRead);
		}
		tBytesRead += iThisRead; // 累积读的大小
		pchBuf += iThisRead; // 移动数组指针位置
	}
}

#define DEFAULT_PORT 6666

int main(int argc, char **argv) {
	int sockfd, acceptfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	unsigned int sin_size, myport = 6666, lisnum = 10;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return -1;
	}
	printf("socket ok\n");
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(DEFAULT_PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 0);

	if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
		perror("bind");
		return -2;
	}

	printf("bind ok\n");
	if (listen(sockfd, lisnum) == -1) {
		perror("listen");
		return -3;
	}
	printf("listen ok\n");
	char recvMsg[10];
	sin_size = sizeof(my_addr);
	acceptfd = accept(sockfd, (struct sockaddr *) &my_addr, &sin_size);
	if (acceptfd < 0) {
		close(sockfd);
		printf("accept failed\n");
		return -4;
	}

	ssize_t readlen = MyRecv(acceptfd, recvMsg, sizeof(int)); // 读取int类型长度,来判断字符串大小
	if (readlen < 0) {
		printf("read failed\n");
		return -1;
	}
	int len = (int) ntohl(*(int *) recvMsg); // 转换成int
	printf("len: %d\n", len);
	readlen = MyRecv(acceptfd, recvMsg, len);
	if (readlen < 0) {
		printf("read failed\n");
		return -1;
	}
	recvMsg[len] = '\0';
	printf("recvMsg: %s\n", recvMsg);
	close(acceptfd);
	return 0;

}