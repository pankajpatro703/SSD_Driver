/*
  ADC_master
  @Author: pankajpatro703
  Reads ADC value and sends it to a SSD driver for displaing on an SSD display.
  This example code is in the public domain.
*/

#include <Wire.h>
#include <SSDmaster.h>

SSDmaster device(0x38);

void setup() {
  Wire.begin();
}

int ldrval;

void loop() {
  ldrval=analogRead(A0);
  device.ssdDisplay(1,B00011100);
  device.ssdDisplay(2,B01111010);
  device.ssdDisplay(3,B00001010);
  device.ssdDisplaynum(4,(byte)ldrval);
  delay(250);  
}
