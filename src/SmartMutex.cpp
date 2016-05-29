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
SmartMutex::SmartMutex(const char * name)
{
	pthread_mutex_init(&m_mutex, NULL);
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
SmartMutex::~SmartMutex()
{
	if (m_name != NULL){
		delete m_name;
	}
	pthread_mutex_destroy(&m_mutex);
}
void SmartMutex::lock()
{	
	struct timespec time;
	clock_gettime(CLOCK_REALTIME,&m_startLockTime);
	time = m_startLockTime;
	time.tv_sec = time.tv_sec + MUTEX_TIMEOUT;
	while(pthread_mutex_timedlock(&m_mutex,&time) != 0){
		struct timespec track;
		clock_gettime(CLOCK_REALTIME, &track);
			cout<<"thread:"<<gettid()<<" wait Mutex:"<<m_name 
				<<" timeout:"<<time.tv_sec - m_startLockTime.tv_sec<<endl;
			cout<<"	> Mutex:"<<m_name<< "owner:"<< m_owner<<endl;
		time.tv_sec += MUTEX_TIMEOUT;
	}
	m_owner = gettid();
}
void SmartMutex::unlock()
{
	pthread_mutex_unlock(&m_mutex);
	m_owner =  -1;
	memset(&m_startLockTime,0, sizeof(struct timespec));
}
