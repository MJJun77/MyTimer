#include <stdio.h>
#include "MyTimer.h"

MyTimer::MyTimer(void (*cbfunc)(union sigval _sigval)) {
	if (cbfunc == nullptr) {
		perror("CB function SHALL BE VALID !!\n");
		m_timerId = 0;
		return;
	}

	struct sigevent loc_sigev;	// I don't know why, but if this is defined as member variable, SIGSEGV happens when calling timer_create()
	loc_sigev.sigev_notify = SIGEV_THREAD;
	loc_sigev.sigev_notify_function = cbfunc;
	loc_sigev.sigev_value.sival_int = 0;

	if (timer_create(CLOCK_MONOTONIC, &loc_sigev, &m_timerId)) {
		perror("timer_create failure !!\n");
		m_timerId = 0;
	}
}

bool MyTimer::startTimer(int sec, int nsec, bool repeat) {
	m_itimerspec.it_value.tv_sec = sec;
	m_itimerspec.it_value.tv_nsec = nsec;
	if (repeat == true) {
		m_itimerspec.it_interval.tv_sec = sec;
		m_itimerspec.it_interval.tv_nsec = nsec;
	}
	else {
		m_itimerspec.it_interval.tv_sec = 0;
		m_itimerspec.it_interval.tv_nsec = 0;
	}

	if (m_timerId == 0) {
		perror("startTimer failure : invalid timer_id\n");
		return false;
	}
	return !timer_settime(m_timerId, 0, &m_itimerspec, nullptr);
}

void MyTimer::cancelTimer() {
	if (m_timerId == 0)
		return;
	m_itimerspec.it_value.tv_sec = 0;
	m_itimerspec.it_value.tv_nsec = 0;
	m_itimerspec.it_interval.tv_sec = 0;
	m_itimerspec.it_interval.tv_nsec = 0;
	timer_settime(m_timerId, 0, &m_itimerspec, nullptr);
}

