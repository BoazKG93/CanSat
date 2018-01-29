# CanSat Project Winter 2018 - TU Berlin 
This project is for learning purposes only. It has been tested on Arduino Nano and Arduno Uno R3.

## Introdruction
The project is divided into two main parts:


1. receiver (ground station)
2. Sender (Satallite system)

The receiver (1) is written in Python 3 and is pretty straightforward, while the sender (2) is a bit more complicated and written in C++.

**Table of Contents**

- [Arduino setup](#arduino-setup)
- [The receiver](#the-receiver)
- [The sender](#the-sender)
- [Editing the files](#editing-the-files)
  - [sender](#sender)
  - [receiver](#receiver)
- [Bugs](#bugs)
- [Contributing](#contributing)
- [Copyright and License](#copyright-and-license)


## Arduino setup
The following sensors and setup are required in order to get things running:
![Circuit board](http://i63.tinypic.com/vzvtcy.jpg)
Also, you will need an XBee transmitor connected to your computer to recieve the data with the receiver.

## The receiver
PySerial is required in order to connect to the Serial in the receiver. You will need to have Python 3 and pip installed. Please check GitHub or the offical website in order to install those. Afterwards run the following command on terminal:

`pip3 install pyserial`

Once the install is over, you are ready to go! it's that easy!

Run the following command on terminal once in the CanSat folder:
`python3 receiver/receiver.py`

You will be asked to write the serial port and bandwidth limit. Afterwards you will be asked for the file name. This file will hold all the collected data 
and will be saved by default in the receiver folder.
Follow the instructions on the terminal, by pressing the Enter key to move forward or CTRL(CMD)+C to leave the session.

## The sender

The sender is a passive component. All you need to do is actually compile and mount it on the Arduino nano. To do so you have to use the terminal. We used the Bare Arduino GitHub project in order to achieve this. This method has been chosen over the Arduino IDE which is horrible. For more information on how to use the terminal compiler and mounter for Arduino, please go to the README file at the sender folder.

## Editing the files

If you want to customize the files to your own needs, only the following files should be edited:
### sender:
* sender/src/CanSatProject/CanSatProject.cpp
* sender/src/CanSatProject/Makefile
* sender/lib/CanSatLib/CanSatLib.cpp
* sender/lib/CanSatLib/CanSatLib.h

To install more libararies, just use the lib folder for it.
### receiver:
* receiver/receiver.py

## Bugs
Not yet registered

## Contribute
Contribution is more than welcome! just commit your changes into a review and we can expand this project to even more bigger and smarter satallites.

## Copyright and license


    The MIT License (MIT)

    Copyright (c) 2018 Boaz Keren Gil

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.


