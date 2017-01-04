#include <stdio.h>

int main(void)
{
	int time;
	int i;
	float s, m, h;
	time = 24 * 60 * 60;
	for(i = 0; i < time; i ++){
		s = i * (360 / 60) % 360;
		m = (i / 60) * (360 / 60) % 360;
		h = (i / 60 / 12) * (360 / 60) % 360;
		if (m == h && m == s) {
			printf("%d:%d:%d，时针、分针、秒针重合。\n", i / 60 / 60, i / 60 % 60, i % 60);
		}
	}
	return 0;
}
