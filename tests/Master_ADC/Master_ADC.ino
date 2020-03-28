#include <Wire.h>

void setup() {
    Wire.begin();        //join i2c bus (address optional for master)
}

void loop() {
    int ldrval=analogRead(A0);        //variable to store ADC data
    ssdDisplay(1,B00011100);          //display L
    ssdDisplay(2,B01111010);          //display D
    ssdDisplay(3,B00001010);          //display R
    ssdDisplaynum(4,(byte)ldrval);    //display ADC value
    delay(250);                       //rate of updation
}

void ssdDisplay(int location,byte value) {
    if(location>6)
        return;                              //validate digit position
    else {
        Wire.beginTransmission(0x38);        //connect to SSD driver    
        Wire.write((byte)(location-1));      //send position
        Wire.endTransmission();              //end communication
        Wire.beginTransmission(0x38);        //connect again to driver
        Wire.write(value);                   //send data for SSD
        Wire.endTransmission();              //end communication
    }
}

void ssdDisplaynum(int location, byte value) {
    if(location>6)
        return;                              //validate digit position
    else if(value>10) {                      //obtain individual digits
        byte rev_num=0;
        while (value > 0) {
            rev_num = rev_num*10 + value%10;
            value = value/10;
        }
        while(rev_num!=0) {
            byte value=B00000000;
            int digit=rev_num%10;
            switch(digit) {                         //Look-Up Table
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
            ssdDisplay(location,value);              //display digit value
            rev_num=rev_num/10;
            location++;
        }
    }
}
