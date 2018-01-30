
def sendToArduino(sendStr):
  ser.write(sendStr.encode())


def recvFromArduino():
  global startMarker, endMarker
  
  ck = ""
  x = "z" # any value that is not an end- or startMarker
  byteCount = -1 # to allow for the fact that the last increment will be one too many
  
  # wait for the start character
  while  ord(x) != startMarker: 
    x = ser.read()
  
  # save data until the end marker is found
  while ord(x) != endMarker:
    if ord(x) != startMarker:
      ck = ck + x.decode('utf-8')
      byteCount += 1
    x = ser.read()
  
  return(ck)


import serial
import time
if __name__ == "__main__":
  # NOTE the user must ensure that the serial port and baudrate are correct
  serPort = input("Please enter the Serial port: ") #"/dev/cu.usbserial-DN02MUUN" 
  baudRate = input("Please enter the Baudrate: ") #9600 #input("Please enter the Baudrate: ")
  fileName = input("Please enter the file name to store the data: ")
  fileName = fileName + ".csv"
  ser = serial.Serial(serPort, baudRate)
  print("Serial port ",serPort," opened  Baudrate ",str(baudRate))
  ser.flushInput()
  ser.flushOutput()
  while ser.inWaiting():
    ser.read()
  startMarker = 60
  endMarker = 62
  input("Turn on sensors?")
  #TODO: Implement a send/rec signal to turn sat online
  sendToArduino("1")
  time.sleep(0.1)
  onlineResponse = recvFromArduino()
  while "Satallite is ready" not in onlineResponse:
      onlineResponse = recvFromArduino()
  if "Satallite is ready" in onlineResponse:
    index = onlineResponse.find("Satallite is ready")
    print(onlineResponse[index:])
    print(recvFromArduino())
    time.sleep(1)
    print(recvFromArduino())
    time.sleep(1)
    print("==================")
    input("Launch it?")
    sendToArduino("1")
    time.sleep(0.5)
    print(recvFromArduino())
    print("==================")
    ser.flushInput()
    ser.flushOutput()
    with open(fileName, 'w+') as the_file:
      the_file.write("Timestamp (s),innerAnalogTemp,outerAnalogTemp,pressure,altitude,AccX,AccY,AccZ,innerDigitalTemp,ServoPosition\n")
      timeout = time.time() + 60
      while True:
  #        time.sleep(0.25)
          timer = 0
          if timer == 5 or time.time() > timeout:
              break
          ser.flushInput()
          ser.flushOutput()
          data = recvFromArduino()
          print(data)
          the_file.write(data)
          the_file.write("\n")
          timer = timer - 1
  #        time.sleep(0.25)
  while ser.inWaiting():
    ser.read()
  ser.flushInput()
  ser.flushOutput()
  ser.close

