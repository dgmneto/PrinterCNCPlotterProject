/*
 * Made by Aloysio Galvão Lopes
 */

//Pin definitions
const int data = 6;
const int latch = 2;
const int clk = 3;
const int en1 = 9;
const int en2 = 10;
const int en3 = 11;

struct StepperData {
  byte data1 = 0;
  byte data2 = 0;
};

//Stepper motor X steps definition defined for clockwise rotation
StepperData motorXSteps(byte id){
  StepperData data;
  switch (id){
    case 0:
    data.data1 = 0b00001000;
    data.data2 = 0b00000000;
    break;
    case 1:
    data.data1 = 0b01001000;
    data.data2 = 0b00000000;
    break;
    case 2:
    data.data1 = 0b01000000;
    data.data2 = 0b00000000;
    break;
    case 3:
    data.data1 = 0b01000100;
    data.data2 = 0b00000000;
    break;
    case 4:
    data.data1 = 0b00000100;
    data.data2 = 0b00000000;
    break;
    case 5:
    data.data1 = 0b00010100;
    data.data2 = 0b00000000;
    break;
    case 6:
    data.data1 = 0b00010000;
    data.data2 = 0b00000000;
    break;
    case 7:
    data.data1 = 0b00011000;
    data.data2 = 0b00000000;
    break;
    }
    return data;
}

//Stepper motor Y steps definition defined for clockwise rotation
StepperData motorYSteps(byte id){
  StepperData data;
  switch (id){
    case 0:
    data.data1 = 0b00000000;
    data.data2 = 0b00001000;
    break;
    case 1:
    data.data1 = 0b00000000;
    data.data2 = 0b00001001;
    break;
    case 2:
    data.data1 = 0b00000000;
    data.data2 = 0b00000001;
    break;
    case 3:
    data.data1 = 0b00000000;
    data.data2 = 0b00000101;
    break;
    case 4:
    data.data1 = 0b00000000;
    data.data2 = 0b00000100;
    break;
    case 5:
    data.data1 = 0b00000000;
    data.data2 = 0b00000110;
    break;
    case 6:
    data.data1 = 0b00000000;
    data.data2 = 0b00000010;
    break;
    case 7:
    data.data1 = 0b00000000;
    data.data2 = 0b00001010;
    break;
    }
    return data;
}

//Stepper motor Z steps definition defined for clockwise rotation
StepperData motorZSteps(byte id){
  StepperData data;
  switch (id){
    case 0:
    data.data1 = 0b00000000;
    data.data2 = 0b00100000;
    break;
    case 1:
    data.data1 = 0b00000010;
    data.data2 = 0b00100000;
    break;
    case 2:
    data.data1 = 0b00000010;
    data.data2 = 0b00000000;
    break;
    case 3:
    data.data1 = 0b00000010;
    data.data2 = 0b00010000;
    break;
    case 4:
    data.data1 = 0b00000000;
    data.data2 = 0b00010000;
    break;
    case 5:
    data.data1 = 0b00000001;
    data.data2 = 0b00010000;
    break;
    case 6:
    data.data1 = 0b00000001;
    data.data2 = 0b00000000;
    break;
    case 7:
    data.data1 = 0b00000001;
    data.data2 = 0b00100000;
    break;
    }
    return data;
}

void setup() {
  //Initializing the pins
  pinMode(data,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(en3,OUTPUT);
}

void loop() {
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  digitalWrite(en3,HIGH);
  // put your main code here, to run repeatedly:
  int total = 30;
  for (int i = 0; i < total; ++i)
  cycle4StepsClockwise(2);
  for (int i = 0; i < total; ++i){
  cycle4StepsCounterClockwise(2);
  }
  
}

//Function which writes data to shift registers
void writeData(byte data1, byte data2){
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, data2);
  shiftOut(data, clk, LSBFIRST, data1);
  digitalWrite(latch, HIGH);
}

//Function whch tests the spin cycle for the stepper
void cycle4StepsClockwise(int sleep){
//writeData(0b01000000, 0b00000000);
//  delay(sleep);
//writeData(0b00010000, 0b00000000);
//  delay(sleep);
//writeData(0b00000100, 0b00000000);
//  delay(sleep);
//writeData(0b00001000, 0b00000000);
//  delay(sleep);
//  writeData(0b00001000, 0b00000000);
//  delay(sleep);
//  writeData(0b01001000, 0b00000000);
//  delay(sleep);
//  writeData(0b01000000, 0b00000000);
//  delay(sleep);
//  writeData(0b01000100, 0b00000000);
//  delay(sleep);
//  writeData(0b00000100, 0b00000000);
//  delay(sleep);
//  writeData(0b00010100, 0b00000000);
//  delay(sleep);
//  writeData(0b00010000, 0b00000000);
//  delay(sleep);
//  writeData(0b00011000, 0b00000000);
//  delay(sleep);
for (int i = 0; i < 7; ++i){
    StepperData data1 = motorZSteps(i);
    StepperData data2 = motorXSteps(i);
    StepperData data3 = motorYSteps(i);
    StepperData toSend;
    toSend.data1 = data1.data1 | data2.data1 | data3.data1;
    toSend.data2 = data1.data2 | data2.data2 | data3.data2;
//    if (i%2 == 0)
    writeData(toSend.data1, toSend.data2);
    delay(sleep);
  }
}
void cycle4StepsCounterClockwise(int sleep){
  for (int i = 7; i >= 0; --i){
    StepperData data1 = motorZSteps(i);
    StepperData data2 = motorXSteps(i);
    StepperData data3 = motorYSteps(i);
    StepperData toSend;
    toSend.data1 = data1.data1 | data2.data1 | data3.data1;
    toSend.data2 = data1.data2 | data2.data2 | data3.data2;
//    if (i%2 == 0)
    writeData(toSend.data1, toSend.data2);
    delay(sleep);
  }
}
