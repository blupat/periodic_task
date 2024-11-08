//=======================================================================
///	@file	PeriodicTask.cpp
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

#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <ros/ros.h>

#include "MainThread.h"

int main(int argc, char* argv[])
{
	int ret;
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGALRM);
	if(pthread_sigmask(SIG_BLOCK, &sigset, NULL) != 0){
		fprintf(stderr, "pthread_sigmask error\n");
		return 1;
	}
	
	ros::init(argc, argv, "periodic_task");
	
	MainThread mainThread;
	return mainThread.Run();
}
