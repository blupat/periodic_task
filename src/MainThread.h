//=======================================================================
///	@file	MainThread.h
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

#ifndef __MAINTHREAD_H
#define __MAINTHREAD_H

#include <stdint.h>
#include <ros/ros.h>
#include <periodic_task/Command.h>

#include "WorkerThread.h"

//-----------------------------------------------------------------------
///	@class	MainThread
///	@brief	
///	@note	
//-----------------------------------------------------------------------

class MainThread{
public:
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	MainThread();

	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	int Run();
	
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	bool Command(periodic_task::Command::Request &req, periodic_task::Command::Response &res);
	
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	void RunWorker();
	
private:
	ros::NodeHandle m_nodeHandle;
	ros::Publisher m_publisher;
	ros::ServiceServer m_serviceServer;
	
	WorkerThread m_worker;
};

#endif	// __MAINTHREAD_H
