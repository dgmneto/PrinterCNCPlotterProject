#ifndef COMMUNICATION
#define COMMUNICATION

#include"SerialClass.h"
#include <tchar.h>
#include <time.h>
#include <algorithm>

#define HEIGHT 40

class Printer
{
    private:
        //Indicates if we have a serial port attached
        bool attached;
        //Indicates if we have a printer connected
        bool connected;
        //Pointer to the serial object to be instantiated;
        Serial* SerialPointer;
        //List of possible COM ports
        bool ports[51];
        //Returns time difference
        long timediff(clock_t t1, clock_t t2);
        //Writes a bit to a char type
        void bitWrite(unsigned char& toWrite, int position, bool bit);
        //Variables for storing position
        int posX;
        int posY;
        int height;
        bool low;
    public:
        //Default constructor
        Printer();
        //Destructor
        ~Printer();
        /**
        *Error code 1:COM not available
        *Error code 2:error at COM port
        *Error code 3:Impossible to get com state
        *Error code 4:Impossible to set serial parameters
        *Error code 5:Already tried the port
        */
        //Attach to port ranging from 0 to 50
        int attach(int port);
        //Getter for attach
        bool getAttach();
        //Connects to the printer (send a code and checks if it really is the printer)
        //This function can take a while to work
        bool connect();
        //Getter for connection
        bool getConnect();
        //Detaches
        void detach();
        //Disconnects
        void disconnect();
        //Writes request for the printer
        bool request(char req);
        //Turns a stepper
        bool turn(int stepper, int steps);
        //Move a stepper
        bool move(int stepper, int steps);
        //Raise the pencil
        bool raise();
        //Lowers the pencil
        bool lower();
        //Get if is lowered
        bool isLowered();
        //Go to position
        bool go(int x, int y);
        //Getters for position
        int getX();
        int getY();
};

#endif
