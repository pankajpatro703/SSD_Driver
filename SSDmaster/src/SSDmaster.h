/*
	SSDmaster.h - Library for sending data to I2C slave SSD driver.
	Created by Pankajkumar Patro, October 25, 2019.
	Released into the public domain.
*/

#ifndef SSDmaster_h
#define SSDmaster_h

#include "Arduino.h"
class SSDmaster
{
	public:
		SSDmaster(int address);
		void ssdDisplay(int location,int value);
		void ssdDisplaynum(int location,int value);
	private:
		int _address,_value;
		int _location;
};

#endif
