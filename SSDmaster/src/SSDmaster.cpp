/*
	SSDmaster.cpp - Library for sending data to I2C slave SSD driver.
	Created by Pankajkumar Patro, October 25, 2019.
	Released into the public domain.
*/

#include "Arduino.h"
#include "SSDmaster.h"
#include "Wire.h"

int toByte(int number) {
  int tmp = number & 0xff;
  return (tmp & 0x80) == 0 ? tmp : tmp - 256;
}

SSDmaster::SSDmaster(int address)
{
	_address=address;
}

void SSDmaster::ssdDisplay(int location, int value)
{
	if(location>6)
		return;
	else
	{
    		Wire.beginTransmission(_address);
    		Wire.write((location-1));
    		Wire.endTransmission();
    		Wire.beginTransmission(_address);
    		Wire.write(toByte(value));
    		Wire.endTransmission();
  	}
}

void SSDmaster::ssdDisplaynum(int location, int value)
{
	if(location>6)
      		return;
  	else if(value>10)
	{
    		int rev_num=0;
    		while (value > 0)
		{
        		rev_num = rev_num*10 + value%10;
        		value = value/10;
    		}
    		while(rev_num!=0)
		{
      			int value=B00000000;
      			int digit=rev_num%10;
      			switch(digit)
			{
        			case 0: value=B11111100; break;
        			case 1: value=B01100000; break;
        			case 2: value=B11011010; break;
        			case 3: value=B11110010; break;
        			case 4: value=B01100110; break;
        			case 5: value=B10110110; break;
        			case 6: value=B10111110; break;
        			case 7: value=B11100000; break;
        			case 8: value=B11111110; break;
        			case 9: value=B11110110; break;
        			default:value=B00000000; break;
      			}
     			ssdDisplay(location,value);
      			rev_num=rev_num/10;
      			location++;
    		}
  	}
}
