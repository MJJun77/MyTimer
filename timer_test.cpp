#include <stdio.h>
#include "MyTimer.h"
#include <unistd.h>

void cb_func_1(union sigval _sigval) {
	printf("main %s is called\n", __FUNCTION__);
}

int main() {
	MyTimer timer_1(cb_func_1);
	timer_1.startTimer(1, 0, true);

	sleep(7);

	return 0;
}

