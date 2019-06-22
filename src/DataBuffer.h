//=======================================================================
///	@file	DataBuffer.h
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

#ifndef __DATABUFFER_H
#define __DATABUFFER_H

#include <stdint.h>

#include "TimeAndSensorData.h"

//-----------------------------------------------------------------------
///	@class	MainThread
///	@brief	
///	@note	
//-----------------------------------------------------------------------

class DataBuffer{
public:
	DataBuffer(int32_t maxLength){
		m_maxBufferLength = maxLength;
		m_buffer[0] = new TimeAndSensorData[m_maxBufferLength];
		m_buffer[1] = new TimeAndSensorData[m_maxBufferLength];
		m_inputBufferIndex = 0;
		m_whichIsOutputBuffer = 1;
	}
	
	~DataBuffer(){
		delete [] m_buffer[0];
		delete [] m_buffer[1];
	}
	
	bool AddData(TimeAndSensorData& data){
		if(m_inputBufferIndex < m_maxBufferLength){
			int32_t whichIsInputBuffer;
			if(m_whichIsOutputBuffer == 0){
				whichIsInputBuffer = 1;
			}else{
				whichIsInputBuffer = 0;
			}
			m_buffer[whichIsInputBuffer][m_inputBufferIndex] = data;
			m_inputBufferIndex++;
			return true;
		}else{
			return false;
		}
	}
	
	TimeAndSensorData* GetBuffer(int32_t& length){
		if(m_whichIsOutputBuffer == 0){
			m_whichIsOutputBuffer = 1;
		}else{
			m_whichIsOutputBuffer = 0;
		}
		length = m_inputBufferIndex;
		m_inputBufferIndex = 0;
		return m_buffer[m_whichIsOutputBuffer];
	}
	
private:
	TimeAndSensorData* m_buffer[2];
	int32_t m_inputBufferIndex;
	int32_t m_whichIsOutputBuffer;
	int32_t m_maxBufferLength;
};

#endif	// __DATABUFFER_H
