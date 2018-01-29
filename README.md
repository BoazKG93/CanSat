# CanSat Project Winter 2018 - TU Berlin 
This project is for learning purposes only. It has been tested on Arduino Nano and Arduno Uno R3.

##Introdruction
The project is divided into two main parts:


1. Reciever (ground station)
2. Sender (Satallite system)

The reciever (1) is written in Python 3 and is pretty straightforward, while the sender (2) is a bit more complicated and written in C++.

##Arduino setup
The following sensors and setup are required in order to get things running:
![Circuit board](http://i67.tinypic.com/oa40tv.jpg)
Also, you will need an XBee transmitor connected to your computer to recieve the data with the reciever.

##The reciever
PySerial is required in order to connect to the Serial in the reciever. You will need to have Python 3 and pip installed. Please check GitHub or the offical website in order to install those. Afterwards run the following command on terminal:

`pip3 install pyserial`

Once the install is over, you are ready to go! it's that easy!

Run the following command on terminal once in the CanSat folder:
`python3 reciever/reciever.py`

You will be asked to write the serial port and bandwidth limit. Afterwards you will be asked for the file name. This file will hold all the collected data 
and will be saved by default in the reciever folder.
Follow the instructions on the terminal, by pressing the Enter key to move forward or CTRL(CMD)+C to leave the session.

##The sender

The sender is a passive component. All you need to do is actually compile and mount it on the Arduino nano. To do so you have to use the terminal. We used the Bare Arduino GitHub project in order to achieve this. This method has been chosen over the Arduino IDE which is horrible. For more information on how to use the terminal compiler and mounter for Arduino, please go to the README file at the sender folder.

##Editing the files

If you want to customize the files to your own needs, only the following files should be edited:
###sender:
* sender/src/CanSatProject/CanSatProject.cpp
* sender/src/CanSatProject/Makefile
* sender/lib/CanSatLib/CanSatLib.cpp
* sender/lib/CanSatLib/CanSatLib.h

To install more libararies, just use the lib folder for it.
###reciever:
* reciever/reciever.py

##Contribute
Contribution is more than welcome! just commit your changes into a review and we can expand this project to even more bigger and smarter satallites.

