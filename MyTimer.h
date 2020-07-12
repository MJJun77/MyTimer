#ifndef __MY_TIMER__HEADER__
#define __MY_TIMER__HEADER__

#include <time.h>
#include <signal.h>

/*
   Timer to call CallBack function when expired.
*/
class MyTimer {
	private:
		timer_t m_timerId;
		struct itimerspec m_itimerspec;
	public:
		static struct sigevent m_sigev;		// sigevent SHALL BE USED AS STATIC !!
		MyTimer(void (*cbfunc)(union sigval _sigval));
		bool startTimer(int sec, int nsec, bool repeat);
		void cancelTimer();
};

//struct sigevent MyTimer::m_sigev = struct sigevent();
#endif

