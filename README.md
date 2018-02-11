# Mini CNC plotter project

This project consists of a mini CNC plotter printer.

There are three main parts in this project the hardware and embedded software, the communication and logic software and the image translator software. Each one will be described.

->Hardware and embedded software: the hardware was fully developed from scratch using three DVD drive stepper motors. Two for moving the plate and one for moving the pen. A circuit board was developed to drive tho motors and an Arduino is used to control them. The embedded software takes care of controlling the motors and sending and receiving serial messages to determine actions and report status. The communication was structured using requests.

All the code for this part is under Arduino_printer folder.

->Communication and logic software: it was developed in code blocks and running on windows serial reader library a code to interpret the messages which are sent by the Arduino. This code provides interface for the other layer of code (logic software) which generates the path for the printer and sends it to the communication. The path is generated based on a txt file which describes and image.

All the code for this part is under Printer_software folder.

->Image translator: this is a python script which translates a png file into a txt fie. This way, the logic software can generate the path.

All the code for this part is under Image_translator folder.
