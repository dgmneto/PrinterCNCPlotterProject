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
const int ledBlue = 4;
const int ledYellow = 5;
const int ledRed = 12;

struct StepperData {
  byte data1 = 0;
  byte data2 = 0;
};

//Stepper motor X steps definition for clockwise rotation
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

//Stepper motor Y steps definition for clockwise rotation
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

//Stepper motor Z steps definition for clockwise rotation
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

//Global variables for the interruption loop
byte motorXCurrentStep = 0;
byte motorYCurrentStep = 0;
byte motorZCurrentStep = 0;
byte motorXState = 0;
byte motorYState = 0;
byte motorZState = 0;
bool test = true;
byte counter = 0;

void setup() {
  //Initializing stepper pins
  pinMode(data,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  pinMode(en3,OUTPUT);

  //Setting up led pins
  pinMode(ledBlue,OUTPUT);
  pinMode(ledYellow,OUTPUT);
  pinMode(ledRed,OUTPUT);

  //Blinking all leds (initialization)
  digitalWrite(ledRed,HIGH);
  delay(150);
  digitalWrite(ledRed,LOW);
  digitalWrite(ledYellow,HIGH);
  delay(150);
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledBlue,HIGH);
  delay(150);
  digitalWrite(ledBlue,LOW);

  //Set timer0 interrupt at 2kHz
  cli();//stop interrupts

  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 60;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);


sei();//allow interrupts

}

void loop() {
  digitalWrite(en1,HIGH);
    digitalWrite(en2,HIGH);
    digitalWrite(en3,HIGH);
//  for (int i = 0; i < 4; ++i){
//  cycle4StepsCounterClockwise(2);
//  }
//    test= true;
//    delay(5000);
//    test = false;
//    delay(5000);
}

//Interrupt to move the steppers
ISR(TIMER1_COMPA_vect){
  if (test){
  motorXCurrentStep = (motorXCurrentStep + 1)%8;}
  else{
  motorXCurrentStep = (motorXCurrentStep - 1)%8;}
  counter++;
  if (counter == 100){
    counter = 0;
    test = !test;
    }
  StepperData toSend;
  StepperData data1 = motorXSteps(motorXCurrentStep);
  toSend.data1 = data1.data1;
  toSend.data2 = data1.data2;
  writeData(toSend.data1, toSend.data2);
}

void writeData(byte data1, byte data2){
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, data2);
  shiftOut(data, clk, LSBFIRST, data1);
  digitalWrite(latch, HIGH);
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
