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

//Library for the I2C master to send data to be displayed to the slave driver.
//////////////////////////////////
//   @Author: pankajpatro703    //
// Licensed under Lesser GPL v3 //
//////////////////////////////////

/*
	SSDmaster.cpp - Library for sending data to I2C slave SSD driver.
	Created by Pankajkumar Patro, October 25, 2019.
	Released under Lesser GPL v3.
*/

#include "Arduino.h"
#include "SSDmaster.h"
#include "Wire.h"

int toByte(int number) {
	/*
	This method converts integers to unsigned bytes. 
	:param number: integer to be converted
	:return: unsigned byte equivalent 
	*/
	int tmp = number & 0xff;
	return (tmp & 0x80) == 0 ? tmp : tmp - 256;
}

SSDmaster::SSDmaster(int address) {
	/*
	This method is a constructor to SSDmaster which initializes the slave address.
	*/	
	_address=address;
}

void SSDmaster::ssdDisplay(int location, int value) {
	/*
	This method displays the character value at a given location.
	:param location: location at which data is to be displayed
	:param value: data to be displayed(in binary) 
	*/
	if(location>6)
		return;
	else {
    	Wire.beginTransmission(_address);
    	Wire.write((location-1));
    	Wire.endTransmission();
    	Wire.beginTransmission(_address);
    	Wire.write(toByte(value));
    	Wire.endTransmission();
  	}
}

void SSDmaster::ssdDisplaynum(int location, int value) {
	/*
	This method displays the decimal digit(0-9) at a given location.
	:param location: location at which digit is to be displayed
	:param value: digit to be displayed(in integer)
	*/
	if(location>6)
    	return;
  	else if(value>10) {
    	int rev_num=0;
    	while (value > 0) {
        	rev_num = rev_num*10 + value%10;
        	value = value/10;
    	}
    	while(rev_num!=0) {
      		int value=B00000000;
      		int digit=rev_num%10;
      		switch(digit) {
        		case 0:  value=B11111100; break;
        		case 1:  value=B01100000; break;
        		case 2:  value=B11011010; break;
        		case 3:  value=B11110010; break;
        		case 4:  value=B01100110; break;
        		case 5:  value=B10110110; break;
        		case 6:  value=B10111110; break;
        		case 7:  value=B11100000; break;
        		case 8:  value=B11111110; break;
        		case 9:  value=B11110110; break;
        		default: value=B00000000; break;
      		}
     		ssdDisplay(location,value);
      		rev_num=rev_num/10;
      		location++;
    	}
  	}
}
