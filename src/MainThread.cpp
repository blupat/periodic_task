//=======================================================================
///	@file	MainThread.cpp
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

#include "MainThread.h"

#include <pthread.h>
#include <periodic_task/TimeAndSensor.h>

#ifdef __cplusplus
extern "C" {
#endif
void* ThreadFunc(void *arg);
#ifdef __cplusplus
}
#endif

void* ThreadFunc(void *arg)
{
	MainThread* mainThread = reinterpret_cast<MainThread*>(arg);
	mainThread->RunWorker();
	return NULL;
}

MainThread::MainThread() : m_nodeHandle()
{
	m_publisher = m_nodeHandle.advertise<periodic_task::TimeAndSensor>("time_and_sensor", 1000);
	m_serviceServer = m_nodeHandle.advertiseService("command", &MainThread::Command, this);
}

int MainThread::Run()
{
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid, NULL, ThreadFunc, reinterpret_cast<void*>(this));
	if(ret != 0){
		ROS_FATAL("cannot create worker");
		return 1;
	}
	
	ros::Rate loopRate(10);
	while (ros::ok())
	{
		ros::spinOnce();

		loopRate.sleep();
	}
	
	m_worker.Abort();
	pthread_join(tid, NULL);
	
	return 0;
}

bool MainThread::Command(periodic_task::Command::Request &req, periodic_task::Command::Response &res)
{
	TimeAndSensorData* data;
	int32_t length;
	if(m_worker.Lock()){
		data = m_worker.GetData(length);
		m_worker.Unlock();
	}else{
		data = 0;
	}
	
	if(data != 0){
		ros::Rate loopRate(10);
		for(int32_t i = 0; i < length; i++){
			periodic_task::TimeAndSensor pubData;
			pubData.time = data[i].time;
			pubData.deltaTime = data[i].deltaTime;
			m_publisher.publish(pubData);
			if((i % 1000) == 999){
				loopRate.sleep();
			}
		}
		ROS_INFO("length = %d", length);
		res.isSucceeded = true;
	}else{
		res.isSucceeded = false;
	}
	return true;
}

void MainThread::RunWorker()
{
	int ret = m_worker.Run();
	if(ret != 0){
		ROS_ERROR("Worker error(%d)", ret);
	}
}
