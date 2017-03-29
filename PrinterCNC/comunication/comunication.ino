
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

//Variables for the comunication loop
bool connection = false;

void loop() {
  // put your main code here, to run repeatedly:
  if (isConnected()) 
   connection = true;
  while (connection){
      byte request = readRequest();
      if (request > 0){
          Serial.print((char)request);
      }
  }
}

//Veryfies connection
bool isConnected(){
    bool validation = false;
    char reading;
    char key[8] = {'p','r','i','n','t','e','r','\0'};
    if (Serial.available() > 0){
      for (int i = 0; i < 7; i++){
         while (!(Serial.available() > 0))
         {}
         validation = true;
         reading = Serial.read();
         if (key[i] != reading){
            validation = false;
            break;
         }
      }
      Serial.print(key);
    }
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

