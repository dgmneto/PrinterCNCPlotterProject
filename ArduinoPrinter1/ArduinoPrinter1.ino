/*
 * Useful info:
 * Stepper 1:
 * Attached at pins 2,4 and 5,6 of shift number one
 * pwm: pin 9
 * Stepper 2:
 * Attached at pins 7,8 of shift number one
 * and attached at pins 3,4 of shift number two
 * pwm: pin 10
 * Stepper 3:
 * Attached at pins 5,6 and 7,8 of shift number two
 * pwm: pin 11
 * Leds:
 * Blue: pin 4,Yellow: pin 5, Red: pin 12
 */

//Constants 
const int data = 6;
const int latch = 2;
const int clk = 3;
const int pwmMot1 = 9;
const int pwmMot2 = 10;
const int pwmMot3 = 11;
const int blueLed = 4;
const int yellowLed = 5;
const int redLed = 12;
 
/*
 * Veryfies if connection has began
 * 
 * @return if connection is established
 */
bool isConnected();

/*
 * Reads the request
 * 
 * @return request
 */
byte readRquest();

/*
 * Function wich writes data to the shift registers
 * 
 * @param data1 data to the first shif register
 * @param data2 data to the second shift register
 */
void writeData(byte data1, byte data2);

/*
 * Class wich controls a stepper motor
 */
class StepperMotor {
  public:
    // Methods
    void turn(int steps); // Generic movement
    void turnC(int steps); // Clockwise movement
    void turnA(int steps); // Anticlockwise movement
    void exeStep(byte x); // Go to step x (1 <= x <= 8)
    void nextStep(); // Go to the next step
    void backStep(); // Go back one step
    StepperMotor(byte id, byte b1, byte b2, byte b3, byte b4);

    // Getters and Setters
    // ID
    byte getStepperID();
    void setStepperID(byte id);
    // stepNumber
    byte getStepNumber();
    void setStepNumber(byte sum);
    // stepperSpeed
    long getStepperSpeed();
    void setStepperSpeed(long intensity);

  private:
    byte b1;
    byte b2; 
    byte b3;
    byte b4;
    static byte dat1;
    static byte dat2;
    byte id;
    byte stepNumber; // From 1 to 8
    long stepperSpeed; // Proportional to delay(t)

};

StepperMotor mot1(1, 6, 5, 4, 2);

StepperMotor mot2(1, 13, 8, 7, 14);

StepperMotor mot3(1, 16, 15, 17, 18);

void setup() {
  // Initializing serial communication with specified baud rate
  Serial.begin(115200);

  //Initializing the pins
  pinMode(data,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(pwmMot1,OUTPUT);
  pinMode(pwmMot2,OUTPUT);
  pinMode(pwmMot3,OUTPUT);
  pinMode(blueLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(redLed,OUTPUT);

  analogWrite(pwmMot1,0);
  analogWrite(pwmMot2,0);
  analogWrite(pwmMot3,0);
  
}

//Variables for the comunication loop
bool connection = false;

void loop() {
  mot1.turn(100);
  mot1.turn(-100);
  digitalWrite(yellowLed, false);
  if (isConnected()){
   connection = true;
   digitalWrite(yellowLed, true);
  }
  while (connection){
      byte request = readRequest();
      if (request > 0){
            byte motor;
            byte moveM;
            bool directionD;
            motor = request/32 - 4;
            
            directionD = ((request/16)|14) - 14;

            moveM = ((request)|240) - 240;

            switch(motor){
            case 1:
              analogWrite(pwmMot1,70);
              analogWrite(pwmMot2,0);
              analogWrite(pwmMot3,0);
              mot1.turn(moveM*(2*directionD-1));
              analogWrite(pwmMot1,0);
              analogWrite(pwmMot2,0);
              analogWrite(pwmMot3,0);
              break;
            case 2:
              analogWrite(pwmMot1,0);
              analogWrite(pwmMot2,50);
              analogWrite(pwmMot3,0);
              mot2.turn(moveM*(2*directionD-1));
              analogWrite(pwmMot1,0);
              analogWrite(pwmMot2,0);
              analogWrite(pwmMot3,0);
              break;
            case 3:      
              analogWrite(pwmMot1,0);
              analogWrite(pwmMot2,0);
              analogWrite(pwmMot3,70);
              mot3.turn(moveM*(2*directionD-1));
              analogWrite(pwmMot1,0);
              analogWrite(pwmMot2,0);
              analogWrite(pwmMot3,0);
              break;
          }
          
          Serial.print((char)request);
      }
  }
}

//Veryfies connection
bool isConnected(){
    bool validation = false;
    char reading;
    char key[8] = {'p','r','i','n','t','e','r'};
    if (Serial.available() > 0){
      digitalWrite(redLed, true);
      for (int i = 0; i < 8; i++){
         while (!(Serial.available() > 0))
         {}
         validation = true;
         reading = Serial.read();
         if (key[i] != reading){
            validation = false;
            break;
         }
      }
      Serial.flush();
      Serial.print(key);
    }
    digitalWrite(redLed, false);
    return validation;
}

//Reads serial request
byte readRequest(){
    byte request;
    if (Serial.available() > 0){
      request = Serial.read();
      return request;
    }
    
    //Code for no request 
    else return 0;
}

//Function wich writes data to shift registers
void writeData(byte data1, byte data2){
  digitalWrite(latch, LOW);
  shiftOut(data, clk, MSBFIRST, data2);
  shiftOut(data, clk, MSBFIRST, data1);
  digitalWrite(latch, HIGH);
}

//Stepper static initializantion
byte StepperMotor::dat1 = 0;
byte StepperMotor::dat2 = 0;

//Stepper class constructor
StepperMotor::StepperMotor(byte id, byte b1, byte b2, byte b3, byte b4){
  this->id = id;
  this->b1 = b1;
  this->b2 = b2;
  this->b3 = b3;
  this->b4 = b4;
  stepNumber = 1;
  stepperSpeed = 10000;
}

//Stepper generic movement
void StepperMotor::turn(int steps)
{
  if (steps > 0)
    turnC(steps);
  else turnA(steps);
}

//Stepper clockwise movement
void StepperMotor::turnC(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    nextStep();
    delayMicroseconds(stepperSpeed);
  }
}

//Stepper anticlockwise movement
void StepperMotor::turnA(int steps)
{
  steps *= (-1);
  for (int i = 0; i < steps; i++)
  {
    backStep();
    delayMicroseconds(stepperSpeed);
  }
}

//Stepper go to step x (1 <= x <= 8)
void StepperMotor::exeStep(byte x)
{
  switch (x)
  {
    case 1:
      if (b1 < 10)
           bitWrite(dat1, b1 - 1, false);
      else bitWrite(dat2, b1 -11, false); 
      if (b2 < 10)
           bitWrite(dat1, b2 - 1, true);
      else bitWrite(dat2, b2 -11, true); 
      if (b3 < 10)
           bitWrite(dat1, b3 - 1, false);
      else bitWrite(dat2, b3 -11, false); 
      if (b4 < 10)
           bitWrite(dat1, b4 - 1, false);
      else bitWrite(dat2, b4 -11, false); 
      writeData(dat1, dat2);
      break;
    case 2:
      if (b1 < 10)
           bitWrite(dat1, b1 - 1, false);
      else bitWrite(dat2, b1 -11, false); 
      if (b2 < 10)
           bitWrite(dat1, b2 - 1, true);
      else bitWrite(dat2, b2 -11, true); 
      if (b3 < 10)
           bitWrite(dat1, b3 - 1, false);
      else bitWrite(dat2, b3 -11, false); 
      if (b4 < 10)
           bitWrite(dat1, b4 - 1, true);
      else bitWrite(dat2, b4 -11, true); 
      writeData(dat1, dat2);
      break;
    case 3:
      if (b1 < 10)
           bitWrite(dat1, b1 - 1, false);
      else bitWrite(dat2, b1 -11, false); 
      if (b2 < 10)
           bitWrite(dat1, b2 - 1, false);
      else bitWrite(dat2, b2 -11, false); 
      if (b3 < 10)
           bitWrite(dat1, b3 - 1, false);
      else bitWrite(dat2, b3 -11, false); 
      if (b4 < 10)
           bitWrite(dat1, b4 - 1, true);
      else bitWrite(dat2, b4 -11, true); 
      writeData(dat1, dat2);
      break;
    case 4:
      if (b1 < 10)
           bitWrite(dat1, b1 - 1, true);
      else bitWrite(dat2, b1 -11, true); 
      if (b2 < 10)
           bitWrite(dat1, b2 - 1, true);
      else bitWrite(dat2, b2 -11, true); 
      if (b3 < 10)
           bitWrite(dat1, b3 - 1, false);
      else bitWrite(dat2, b3 -11, false); 
      if (b4 < 10)
           bitWrite(dat1, b4 - 1, true);
      else bitWrite(dat2, b4 -11, true); 
      writeData(dat1, dat2);
      break;
    case 5:
      if (b1 < 10)
           bitWrite(dat1, b1 - 1, true);
      else bitWrite(dat2, b1 -11, true); 
      if (b2 < 10)
           bitWrite(dat1, b2 - 1, false);
      else bitWrite(dat2, b2 -11, false); 
      if (b3 < 10)
           bitWrite(dat1, b3 - 1, false);
      else bitWrite(dat2, b3 -11, false); 
      if (b4 < 10)
           bitWrite(dat1, b4 - 1, false);
      else bitWrite(dat2, b4 -11, false); 
      writeData(dat1, dat2);
      break;
    case 6:
      if (b1 < 10)
           bitWrite(dat1, b1 - 1, true);
      else bitWrite(dat2, b1 -11, true); 
      if (b2 < 10)
           bitWrite(dat1, b2 - 1, false);
      else bitWrite(dat2, b2 -11, false); 
      if (b3 < 10)
           bitWrite(dat1, b3 - 1, true);
      else bitWrite(dat2, b3 -11, true); 
      if (b4 < 10)
           bitWrite(dat1, b4 - 1, false);
      else bitWrite(dat2, b4 -11, false); 
      writeData(dat1, dat2);
      break;
    case 7:
      if (b1 < 10)
           bitWrite(dat1, b1 - 1, false);
      else bitWrite(dat2, b1 -11, false); 
      if (b2 < 10)
           bitWrite(dat1, b2 - 1, false);
      else bitWrite(dat2, b2 -11, false); 
      if (b3 < 10)
           bitWrite(dat1, b3 - 1, true);
      else bitWrite(dat2, b3 -11, true); 
      if (b4 < 10)
           bitWrite(dat1, b4 - 1, false);
      else bitWrite(dat2, b4 -11, false); 
      writeData(dat1, dat2);
      break;
    case 8:
      if (b1 < 10)
           bitWrite(dat1, b1 - 1, false);
      else bitWrite(dat2, b1 -11, false); 
      if (b2 < 10)
           bitWrite(dat1, b2 - 1, true);
      else bitWrite(dat2, b2 -11, true); 
      if (b3 < 10)
           bitWrite(dat1, b3 - 1, true);
      else bitWrite(dat2, b3 -11, true); 
      if (b4 < 10)
           bitWrite(dat1, b4 - 1, false);
      else bitWrite(dat2, b4 -11, false); 
      writeData(dat1, dat2);
      break;
  }
}

//Stepper go to the next step
void StepperMotor::nextStep()
{
  stepNumber = (stepNumber % 8) + 1;
  exeStep(stepNumber);
}

//Stepper go back one step
void StepperMotor::backStep()
{
  stepNumber = (stepNumber + 6) % 8 + 1;
  exeStep(stepNumber);
}

//Stepper getter and setter ID
byte StepperMotor::getStepperID()
{
  return id;
}

void StepperMotor::setStepperID(byte id)
{
  this->id = id;
}

//Stepper getter and setter stepNumber
byte StepperMotor::getStepNumber()
{
  return stepNumber;
}
void StepperMotor::setStepNumber(byte sum)
{
  if (sum == 1)
    stepNumber = (stepNumber % 8) + 1;
  else if (sum == -1)
    stepNumber = (stepNumber + 6) % 8 + 1;
}

//Stepper detter and setter stepperSpeed
long StepperMotor::getStepperSpeed()
{
  return stepperSpeed;
}
void StepperMotor::setStepperSpeed(long intensity)
{
  stepperSpeed = intensity;
}

