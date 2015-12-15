
#ifndef THREAD_H_
# define THREAD_H_

#if (defined __linux__) || (defined __APPLE__)
# include <pthread.h>
#elif defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#endif

# include <functional>
# include <iostream>
# include <utility>
# include <cstring>

template <typename T>
class Thread
{
public:
	typedef std::function<void(T)> ThreadFunc;

public:
	Thread(ThreadFunc func, T data)
	{
		std::pair<ThreadFunc, T>*	pairdata;

		pairdata = new std::pair<ThreadFunc, T>;
		pairdata->first = func;
		pairdata->second = data;
#if (defined __linux__) || (defined __APPLE__)
		if (pthread_create(&_thread, NULL, &Thread::_runFunc, pairdata) != 0)
			throw std::exception();
#elif defined(_WIN32)	
		if ((_handle = CreateThread(NULL, 0, _runFunc, pairdata, 0, NULL)) == NULL)
			throw std::exception();
#endif
	}

	~Thread() {}

public:

	void		join() {
#if (defined __linux__) || (defined __APPLE__)
		if (pthread_join(_thread, NULL) != 0)
			throw std::exception();
#elif defined(_WIN32)
		if (WaitForSingleObject(_handle, INFINITE) == WAIT_FAILED)
			throw std::exception();
#endif
	}

private:
#if (defined __linux__) || (defined __APPLE__)
	static void*	_runFunc(void* data) {
#elif defined(_WIN32)	
	static DWORD WINAPI	_runFunc(void* data) {
#endif
		std::pair<ThreadFunc, T>*	tmp;

		tmp = static_cast<std::pair<ThreadFunc, T>* >(data);
		(tmp->first)(tmp->second);
		delete tmp;
#if (defined __linux__) || (defined __APPLE__)
		pthread_exit(NULL);
#elif defined(_WIN32)	
		ExitThread(0);
#endif
	}

private:
#if (defined __linux__) || (defined __APPLE__)
	pthread_t	_thread;
#elif defined(_WIN32)	
	HANDLE _handle;
#endif
};

#endif /* !THREAD_H_ */
