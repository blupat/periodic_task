//=======================================================================
///	@file	TimeAndSensorData.h
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

#ifndef __TIMEANDSENSORDATA_H
#define __TIMEANDSENSORDATA_H

#include <stdint.h>

//-----------------------------------------------------------------------
///	@class	MainThread
///	@brief	
///	@note	
//-----------------------------------------------------------------------

class TimeAndSensorData{
public:
	double time;
	double deltaTime;
	int16_t leftForward;
	int16_t leftSide;
	int16_t rightSide;
	int16_t rightForward;
};

#endif	// __TIMEANDSENSORDATA_H
