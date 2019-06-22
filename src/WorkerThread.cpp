//=======================================================================
///	@file	WorkerThread.cpp
///	@brief	
///	@note	
//	
//	Copyright (C) 2019 Yasushi Oshima (oosmyss@gmail.com)
//	
//	 This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//	 This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//=======================================================================

#include "WorkerThread.h"

#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

#include "TimeAndSensorData.h"

WorkerThread::WorkerThread() : m_buffer(0x10000)
{
	pthread_mutex_init(&m_mutex, NULL);
	m_isAborted = false;
}

int WorkerThread::Run()
{
	static const int THREAD_PRIORITY = 99;
	struct sched_param param;
	sigset_t sigset;
	timer_t timerid;
	const struct timespec TIME_SPEC = {
		0, INTERVAL_TIME
	};
	const struct itimerspec INTERVAL_TIMER_SPEC = {
		TIME_SPEC, TIME_SPEC
	};
	
	param.sched_priority = THREAD_PRIORITY;
	if(sched_setscheduler(0, SCHED_FIFO, &param) != 0){
		return 1;
	}
	
	if(timer_create(CLOCK_MONOTONIC, NULL, &timerid) != 0){
		return 2;
	}
	if(timer_settime(timerid, 0, &INTERVAL_TIMER_SPEC, NULL) != 0){
		return 3;
	}
	
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGALRM);
	
	double previousTime = 0.0;
	while(!m_isAborted){
		int signo;
		struct timeval tv;
		TimeAndSensorData data;

		sigwait(&sigset, &signo);

		gettimeofday(&tv, NULL);
		data.time = static_cast<double>(tv.tv_sec) + 0.000001 * tv.tv_usec;
		data.deltaTime = data.time - previousTime;
		if(TryLock()){
			m_buffer.AddData(data);
			Unlock();
		}
		previousTime = data.time;
	}
	return 0;
}

bool WorkerThread::Lock(){
	if(pthread_mutex_lock(&m_mutex) == 0){
		return true;
	}else{
		return false;
	}
}

bool WorkerThread::TryLock(){
	if(pthread_mutex_trylock(&m_mutex) == 0){
		return true;
	}else{
		return false;
	}
}

bool WorkerThread::Unlock(){
	if(pthread_mutex_unlock(&m_mutex) == 0){
		return true;
	}else{
		return false;
	}
}
