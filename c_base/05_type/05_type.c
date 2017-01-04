#include <stdio.h>

int main() {
    int i = 117;// 定义整型变量i=117
    char a = 'm';    // 定义字符型变量a
    float m = 123.1234567;    // 定义浮点型变量m
    printf("以整型输出i\t\t\t%d\n", i);    // 以整型输出i
    printf("以字符型输出i\t\t\t%c\n", i);    // 以字符型输出i
    printf("以八进制形式输出i\t\t%o\n", i);    // 以八进制形式输出i
    printf("以十六进制小写形式输出i\t\t%x\n", i);    // 以十六进制小写形式输出i
    printf("以十六进制大写形式输出i\t\t%X\n", i);    // 以十六进制大写形式输出i
    printf("以字符型输出a\t\t\t%c\n", a);    // 以字符型输出a
    printf("以整型输出a\t\t\t%d\n", a);    // 以整型输出a
    printf("以八进制形式输出a\t\t%o\n", a); // 以八进制形式输出a
    printf("以十六进制小写形式输出a\t\t%x\n", a);    // 以十六进制小写形式输出a
    printf("以十六进制大写形式输出a\t\t%X\n", a);    // 以十六进制大写形式输出a
    printf("以浮点型输出m\t\t\t%f\n", m);    // 以浮点型输出m
    printf("以科学计数法输出m\t\t%e\n", m);    // 以科学计数法输出m
    return 0;
}

