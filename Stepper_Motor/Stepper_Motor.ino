//Constants 
const int data = 6;
const int latch = 2;
const int clk = 3;

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

/*
 * Writes data to the shift registers
 * 
 * @param data1 data to be written to the first shift register
 * @param data2 data to be written to the second shift register
 */
void writeData(byte data1, byte data2);

class StepperMotor {
  public:
    // Methods
    void turn(int steps); // Generic movement
    void turnC(int steps); // Clockwise movement
    void turnA(int steps); // Anticlockwise movement
    void exeStep(int x); // Go to step x (1 <= x <= 8)
    void nextStep(); // Go to the next step
    void backStep(); // Go back one step
    StepperMotor(int stepNumber);

    // Getters and Setters
    // ID
    int getStepperID();
    void setStepperID(int id);
    // stepNumber
    int getStepNumber();
    void setStepNumber(int sum);
    // positionValue
    int getPositionValue();
    void setPositionValue(int sum);
    // stepperSpeed
    double getStepperSpeed();
    void setStepperSpeed(double intensity);

  private:
    int ID;
    int stepNumber; // From 1 to 8
    int positionValue; // Acumulated sum of the steps
    double stepperSpeed; // Inversely proportional to delay(t)

};

// Constructor
StepperMotor::StepperMotor(int stepNumber)
{
  this->stepNumber = stepNumber;
}

// Generic movement
void StepperMotor::turn(int steps)
{
  if (steps > 0)
    turnC(steps);
  else turnA(steps);
}

// Clockwise movement
void StepperMotor::turnC(int steps)
{
  for (int i = 0; i < steps; i++)
  {
    nextStep();
    delay(1);
  }
}

// Anticlockwise movement
void StepperMotor::turnA(int steps)
{
  steps *= (-1);
  for (int i = 0; i < steps; i++)
  {
    backStep();
    delay(1);
  }
}

// Go to step x (1 <= x <= 8)
void StepperMotor::exeStep(int x)
{
  switch (x)
  {
    case 1:

      writeData(B00010000, 0);
      
      /*
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);*/
      break;
    case 2:
      writeData(B00010100, 0);
     /* digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);*/
      break;
    case 3:
      writeData(B00000100, 0);
     /* digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);*/
      break;
    case 4:
      writeData(B01000100, 0);
   /*   digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);*/
      break;
    case 5:
      writeData(B01000000, 0);
    /*  digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);*/
      break;
    case 6:
      writeData(B01001000, 0);
     /* digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);*/
      break;
    case 7:
      writeData(B00001000, 0);
    /*  digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);*/
      break;
    case 8:
      writeData(B00011000, 0);
     /* digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);*/
      break;
  }
}

// Go to the next step
void StepperMotor::nextStep()
{
  stepNumber = (stepNumber % 8) + 1;
  positionValue++;
  exeStep(stepNumber);
}

// Go back one step
void StepperMotor::backStep()
{
  stepNumber = (stepNumber + 6) % 8 + 1;
  positionValue--;
  exeStep(stepNumber);
}

// Getter e setter ID
int StepperMotor::getStepperID()
{
  return ID;
}
void StepperMotor::setStepperID(int id)
{
  ID = id;
}

// Getter e setter stepNumber
int StepperMotor::getStepNumber()
{
  return stepNumber;
}
void StepperMotor::setStepNumber(int sum)
{
  if (sum == 1)
    stepNumber = (stepNumber % 8) + 1;
  else if (sum == -1)
    stepNumber = (stepNumber + 6) % 8 + 1;
}

// Getter e setter positionValue
int StepperMotor::getPositionValue()
{
  return positionValue;
}
void StepperMotor::setPositionValue(int sum)
{
  positionValue += sum;
}

// Getter e setter stepperSpeed
double StepperMotor::getStepperSpeed()
{
  return stepperSpeed;
}
void StepperMotor::setStepperSpeed(double intensity)
{
  stepperSpeed = intensity;
}


StepperMotor motor(1);

void setup() {
  //Initializing pins
  Serial.begin(9600);
  StepperMotor motor(1);
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
  analogWrite(9, 70); // Ajuste da tensão, deixa mais fraco ou mais forte
 // shiftOut(11, 12, LSBFIRST, B01000000);
 /* digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);*/

}

void loop() {
  while(1){
 motor.turn(-100);
 // delay(1000);
 motor.turn(100);
 // delay(1000);
   digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, B11111111);
  shiftOut(data, clk, LSBFIRST, B11111111);
  digitalWrite(latch, HIGH);
  delay(1000);
 digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, B00000000);
  shiftOut(data, clk, LSBFIRST, B00000000);
  digitalWrite(latch, HIGH);
  delay(1000);


Serial.println("aqui");
  }
  /* // Reading the sensor value
    int sensorReading = analogRead(A0);
    Serial.println(sensorReading);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(5);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(5);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(5);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    delay(5);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    delay(5);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(5);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(5);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(5);*/
}

void writeData(byte data1, byte data2){
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, data2);
  shiftOut(data, clk, LSBFIRST, data1);
  digitalWrite(latch, HIGH);
}

