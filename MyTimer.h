#ifndef __MY_TIMER__HEADER__
#define __MY_TIMER__HEADER__

#include <time.h>
#include <signal.h>

/*
   Timer to call CallBack function when expired.
*/
class MyTimer {
	private:
		struct sigevent m_sigev;	
		    // -> Shall NOT be used !!  Don't know why, but when member var is used, SIGSEGV happens when timer_create().
			// -> Not used, but SHALL BE DEFINED in g++ v9.3.0 !! Bug ??  If it is not defined, timer doesn't invoked !!
		timer_t m_timerId;
		struct itimerspec m_itimerspec;
	public:
		MyTimer(void (*cbfunc)(union sigval _sigval));
		bool startTimer(int sec, int nsec, bool repeat);
		void cancelTimer();
};

#endif

