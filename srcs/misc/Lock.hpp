
#ifndef LOCK_H_
# define LOCK_H_

#if defined(__linux__)
# include <pthread.h>
#elif defined(_WIN32)
# include <Windows.h>
#endif

class Lock {
public:
	Lock();
	~Lock();

	void lock();
	bool try_lock();
	void unlock();

private:
	#if defined(__linux__)
	pthread_mutex_t _lock;
	#elif defined(_WIN32)	
	CRITICAL_SECTION _lock;
	#endif
};

#endif /* !LOCKGUARD_H_ */