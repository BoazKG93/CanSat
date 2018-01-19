from functions import *
import serial
import time

if __name__ == "__main__":
  # NOTE the user must ensure that the serial port and baudrate are correct
  serPort = raw_input("Please enter the Serial port: ")
  baudRate = input("Please enter the Baudrate: ")
  ser = serial.Serial(serPort, baudRate)
  print "Serial port " + serPort + " opened  Baudrate " + str(baudRate)


  startMarker = 60
  endMarker = 62

  sendData = []

  input("Press Enter to turn the satallite on")

  sendData.append(1) #1 is online signal

  communicate(sendData)

  #Receive data for 5 minutes
  timeout = time.time() + 60*5
  while True:
      time.sleep(0.5)
      timer = 0
      if timer == 5 or time.time() > timeout:
          break
      data = recvFromArduino()
      print data
      #TODO: Save to CSV
      time.sleep(0.5)
      timer = timer - 1

  ser.close

