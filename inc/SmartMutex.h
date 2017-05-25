#ifndef SMARTMUTEX_H
#define SMARTMUTEX_H
#include "pthread.h"
#define MUTEX_TIMEOUT 30 //s
class SmartMutexBasic{
	private:
		int				m_owner;
		struct timespec m_startLockTime;
		char *			m_name;
	public:
		SmartMutexBasic(const char *);
		~SmartMutexBasic();
		pid_t 			getOwner 	();
		const char *	getName 	();
		virtual void 	lock		();
		virtual void 	unlock		();
};
class SmartMutex:public SmartMutexBasic{
	private:
		pthread_mutex_t m_mutex;
	public:
		SmartMutex(const char *);
		~SmartMutex();
		virtual void lock();
		virtual void unlock();
};
class SmartRWLock:public SmartMutexBasic{
	private:
		pthread_rwlock_t m_mutex;
		unsigned int 	m_RD_ref;
	public:
		SmartRWLock(const char *);
		~SmartRWLock();
		void rdlock();
		void wrlock();
		virtual void unlock();
};
#endif//SMARTMUTEX_H
