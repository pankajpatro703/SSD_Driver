/*
    Copyright 2019, 2020 Pankajkumar Patro
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//Header library for the I2C master to send data to be displayed to the slave driver.
//////////////////////////////////
//   @Author: pankajpatro703    //
// Licensed under Lesser GPL v3 //
//////////////////////////////////

/*
	SSDmaster.h - Library for sending data to I2C slave SSD driver.
	Created by Pankajkumar Patro, October 25, 2019.
	Released under Lesser GPL v3.
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
