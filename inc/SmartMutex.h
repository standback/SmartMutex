#ifndef SMARTMUTEX_H
#define SMARTMUTEX_H
#include "pthread.h"
#define MUTEX_TIMEOUT 30 //s
class SmartMutex{
	private:
		pthread_mutex_t m_mutex;
		int				m_owner;
		struct timespec m_startLockTime;
		char *			m_name;
	public:
		SmartMutex(const char *);
		~SmartMutex();
		void lock();
		void unlock();
};
#endif//SMARTMUTEX_H
