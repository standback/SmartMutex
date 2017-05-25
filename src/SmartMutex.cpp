#include <iostream>
#include <unistd.h>
#include "time.h"
#include <sys/types.h>
#include "stdio.h"
#include "string.h"
#include "SmartMutex.h"
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
using namespace std;
SmartMutexBasic::SmartMutexBasic(const char *name){

	if (name == NULL)
	{
		m_name = new char[6];//not define,use pthread_id
		snprintf(m_name,5,"%lu", pthread_self());
	}
	else{
		m_name = new char[strlen(name)+1];
		memcpy(m_name, name, strlen(name)+1);
	}	
}
SmartMutexBasic::~SmartMutexBasic()
{
	if (m_name != NULL){
		delete m_name;
	}

}
void SmartMutexBasic::lock()
{
	clock_gettime(CLOCK_REALTIME,&m_startLockTime);
	m_owner = gettid();
}
void SmartMutexBasic::unlock()
{

	m_owner =  -1;
	memset(&m_startLockTime,0, sizeof(struct timespec));
}
pid_t SmartMutexBasic::getOwner()
{
	return m_owner;
}
const char * SmartMutexBasic::getName()
{
	return m_name;
}
/*
*
* 	SmartMutex
*
*/
SmartMutex::SmartMutex(const char * name):
	SmartMutexBasic(name)
{
	pthread_mutex_init(&m_mutex, NULL);

}
SmartMutex::~SmartMutex()

{
	pthread_mutex_destroy(&m_mutex);
}
void SmartMutex::lock()
{	
	struct timespec time,start;
	clock_gettime(CLOCK_REALTIME, &start);
	time = start;
	time.tv_sec = time.tv_sec + MUTEX_TIMEOUT;
	while(pthread_mutex_timedlock(&m_mutex,&time) != 0){
		struct timespec track;
		clock_gettime(CLOCK_REALTIME, &track);
			cout<<"thread:"<<gettid()<<" ,wait Mutex:"<< getName() 
				<<", timeout:"<<time.tv_sec - start.tv_sec<<endl;
			cout<<"	> Mutex:"<<getName()<< ", owner:"<< getOwner()<<endl;
		time.tv_sec += MUTEX_TIMEOUT;
	}
	SmartMutexBasic::lock();
}
void SmartMutex::unlock()
{
	SmartMutexBasic::unlock();
	pthread_mutex_unlock(&m_mutex);
}
