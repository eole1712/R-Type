
#include "Lock.hpp"

Lock::Lock() {
#if (defined __linux__) || (defined __APPLE__)
	int ret;
		
	ret = pthread_mutex_init(&_lock, NULL);
	if (ret == EAGAIN || ret == ENOMEM ||ret == EINVAL)
    	throw std::exception();
#elif defined(_WIN32)	
	InitializeCriticalSection(&_lock);
#endif
}

Lock::~Lock() {
#if (defined __linux__) || (defined __APPLE__)
	int	ret;
	ret = pthread_mutex_destroy(&_lock);
	if (ret == EBUSY || ret == EINVAL)
    	throw std::exception();
#elif defined(_WIN32)	
    DeleteCriticalSection(&_lock);
#endif 
}

void	Lock::lock() {
#if (defined __linux__) || (defined __APPLE__)
	int	ret;

	ret = pthread_mutex_lock(&_lock);
 	if (ret == EDEADLK || ret == EINVAL)
    	throw std::exception();
#elif defined(_WIN32)
    EnterCriticalSection(&_lock);
#endif 
}

void	Lock::unlock()
{
#if (defined __linux__) || (defined __APPLE__)
	int	ret;

	ret = pthread_mutex_unlock(&_lock);
 	if (ret == EINVAL || ret == EPERM)
    	throw std::exception();
#elif defined(_WIN32)
    LeaveCriticalSection(&_lock);
#endif 
}

bool	Lock::try_lock()
{
#if (defined __linux__) || (defined __APPLE__)
 	int	ret;

	if ((ret = pthread_mutex_trylock(&_lock)) == EBUSY)
   		return (false);
 	else if (ret != 0)
    	throw std::exception();
  	return (true);
#elif defined(_WIN32)
	return TryEnterCriticalSection(&_lock);
#endif 
}