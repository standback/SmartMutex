#include "pthread.h"
#include "sys/prctl.h"
#include "unistd.h"
#include "SmartMutex.h"
class SmartMutex myMutex("mutexTest");
static void * mythread(void *)
{
	prctl(PR_SET_NAME, "SmartMutexTestSub");
	myMutex.lock();
		sleep(100);
	myMutex.unlock();		
}
int main(){
	pthread_t threadid;
	prctl(PR_SET_NAME,"SmartMutexTestMain");
	pthread_create(&threadid,NULL,mythread,NULL);
	myMutex.lock();
		sleep(100);
	myMutex.unlock();
}
