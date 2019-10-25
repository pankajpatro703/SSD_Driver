#include <Wire.h>
int flag=1;
int m=0,n=0;
int arr[6]={0,0,0,0,0,0};
void setup() {
  Wire.begin(0x38);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(10);
  for(int i=0;i<6;i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void callforsegment(int a) {
  if(flag%2==1)
    m=a;
  else
  {
    n=a;
    flag=0;
  }
  arr[m]=n;
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) {  // loop through all but the last
    char c = Wire.read();         // receive byte as a character
    //Serial.print(c);              // print the character
  }
  int x = Wire.read();            // receive byte as an integer
  //Serial.println(x);              // print the integer
  callforsegment(x);
  flag++;
}
