/*
 * Made by Aloysio Galvão Lopes
 */

//Pin definitions
const int data = 6;
const int latch = 2;
const int clk = 3;
const int en1 = 9;

void setup() {
  //Initializing the pins
  pinMode(data,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(en1,OUTPUT);
}

void loop() {
  digitalWrite(en1,HIGH);
  // put your main code here, to run repeatedly:
  int total = 40;
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
  writeData(0b00001000, 0b00000000);
  delay(sleep);
  writeData(0b01001000, 0b00000000);
  delay(sleep);
  writeData(0b01000000, 0b00000000);
  delay(sleep);
  writeData(0b01000100, 0b00000000);
  delay(sleep);
  writeData(0b00000100, 0b00000000);
  delay(sleep);
  writeData(0b00010100, 0b00000000);
  delay(sleep);
  writeData(0b00010000, 0b00000000);
  delay(sleep);
  writeData(0b00011000, 0b00000000);
  delay(sleep);
}
void cycle4StepsCounterClockwise(int sleep){
  writeData(0b00011000, 0b00000000);
  delay(sleep);
  writeData(0b00010000, 0b00000000);
  delay(sleep);
  writeData(0b00010100, 0b00000000);
  delay(sleep);
  writeData(0b00000100, 0b00000000);
  delay(sleep);
  writeData(0b01000100, 0b00000000);
  delay(sleep);
  writeData(0b01000000, 0b00000000);
  delay(sleep);
  writeData(0b01001000, 0b00000000);
  delay(sleep);
  writeData(0b00001000, 0b00000000);
  delay(sleep);
}
