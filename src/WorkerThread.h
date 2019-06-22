//=======================================================================
///	@file	WorkerThread.h
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

#ifndef __WORKERTHREAD_H
#define __WORKERTHREAD_H

#include <stdint.h>
#include <pthread.h>

#include "TimeAndSensorData.h"
#include "DataBuffer.h"

//-----------------------------------------------------------------------
///	@class	WorkerThread
///	@brief	
///	@note	
//-----------------------------------------------------------------------

class WorkerThread{
public:
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	WorkerThread();

	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	int Run();
	
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	TimeAndSensorData* GetData(int32_t& length){
		return m_buffer.GetBuffer(length);
	}
	
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	bool Lock();
	
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	bool TryLock();
	
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	bool Unlock();
	
	//-----------------------------------------------------------------------
	///	@brief	
	///	@note	
	//-----------------------------------------------------------------------
	void Abort(){
		m_isAborted = true;
	}
	
private:
	static const int32_t INTERVAL_TIME = 200000;	// 5KHz

	DataBuffer m_buffer;
	pthread_mutex_t m_mutex;
	bool m_isAborted;
};

#endif	// __WORKERTHREAD_H
