#include "Communication.h"

//Initializing printer communication parameters
Printer::Printer(){
    //Initializing variables
    attached = false;
    connected = false;
    SerialPointer = NULL;
    posX = 0;
    posY = 0;
    height = 0;
    for (int i = 0; i < 51; ++i)
        ports[i] = true;
}

//Printer destructor
Printer::~Printer(){
    if (SerialPointer != NULL)
        delete SerialPointer;
}

//Attach printer to a serial port
int Printer::attach(int port){
    int error = 0;

    //If we have instantiated a serial object
    if (SerialPointer != NULL){
        delete SerialPointer;
        attached = false;
    }
    SerialPointer = NULL;

    //Checking if an error has already occurred
    if (ports[port] == false){
        error = 5;
        return error;
    }

    //Creating serial object
    SerialPointer = new Serial(port);
    error = SerialPointer->getError();

    //Checking if it is attached
    if (error == 0) attached = true;

    //Invalidating ports
    if (error > 0)
        ports[port] = false;
    return error;
}

//Establishing connection
bool Printer::connect(){
    //If the printer is not attached there is no reason to connect
    if (!attached)
        return false;
    //Flush on serial
    SerialPointer->Flush();
    //Key to be tested
    char connectionTest[8] = {'p','r','i','n','t','e','r'};
        //One char string to be written
        char output[1];

        //Writing the string
        for (int i = 0; i < 10; i++){
            output[0] = connectionTest[i];
            SerialPointer->WriteData(output, 1);
        }

        //String that holds the incoming data
        char incomingData[256] = "";

        //Receiving message from the printer
        //Checks if there is nothig to be read
        int readResult = 0;

        //Calculates the time difference
        clock_t ti, tf;
        ti = clock();

        //Flag for timeout
        bool timeoutflag = false;

        //Reading loop
        do{
            Sleep(100);
            tf = clock();
            if (timediff(ti, tf) > 6200)
                timeoutflag = true;
            readResult = SerialPointer->ReadData(incomingData,7);
        } while(readResult == 0 && !timeoutflag);

        //Writing the \0
        incomingData[readResult] = 0;

        //Comparing with the key
        if (!strcmp(incomingData, "printer")){
             connected = true;
             return true;
        }

        //If there was no match
        else return false;
}

//Getter for attach
bool Printer::getAttach(){
    return attached;
}

//Getter for connection
bool Printer::getConnect(){
    return connected;
}

//Detach
void Printer::detach(){
    //If we have instantiated a serial object
    if (SerialPointer != NULL)
        delete SerialPointer;
    SerialPointer = NULL;
    attached = false;
}

//Disconnect
void Printer::disconnect(){
    connected = false;
}

//Writes request
bool Printer::request(char req){
    if (!connected)
        return false;

    //Variable to write request to serial object
    char output[1];
    output[0] = req;

    //Flush on serial
    SerialPointer->Flush();

    //Writing to serial object
    SerialPointer->WriteData(output, 1);

    //Block for reading and detecting errors
    char incomingData[256] = "";
    int readResult = 0;
    clock_t ti, tf;
    ti = clock();

    do{
        tf = clock();
        if (timediff(ti, tf) > 20000)
            return false;
        readResult = SerialPointer->ReadData(incomingData,255);
    } while(readResult == 0);

    //Write went well
    if (incomingData[0] == req)
        return true;

    //Request problem
    return false;
}

//Moves the stepper
bool Printer::move(int stepper, int steps){
    //To be returned
    bool wentOk = true;

    //Movement direction
    bool dir = steps >= 0;

    //In case steps is negative
    if (steps < 0)
        steps = -steps;

    while (steps > 0 && wentOk){

        //Decrementing steps
        steps--;

        //Performing move
        if (dir)
             wentOk = turn(stepper, 1);
        else wentOk = turn(stepper, -1);
        Sleep(10);
    }

    return wentOk;
}

//Turns a stepper
bool Printer::turn(int stepper, int steps){
    //Preparing request
    unsigned char req = stepper;
    req *= 32;
    bitWrite(req, 7, 1);
    if (steps > 0)
        bitWrite(req, 4, 1);

    //Selecting stepper
    switch (stepper){
    case 1:
        posX+=steps;
        break;
    case 2:
        posY+= steps;
        break;
    case 3:
        height+=steps;
        break;
    }

    if (steps >= 0)
         req += steps;
    else req -= steps;

    return request(req);
}

//Function to write a bit
void Printer::bitWrite(unsigned char& toWrite, int position, bool bit){
    unsigned char byte = 1;

    byte <<= position;

    toWrite |= byte;
    if (bit == false)
        toWrite -= byte;
}

//Function for time difference
long Printer::timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}
