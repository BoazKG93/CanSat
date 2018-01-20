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


def waitForArduino():

   # wait until the Arduino sends 'Arduino Ready' - allows time for Arduino reset
   # it also ensures that any bytes left over from a previous message are discarded
   
    global startMarker, endMarker
    
    msg = ""
    while msg.find("Satallite is ready") == -1:

      while ser.inWaiting() == 0:
        pass
        
      msg = recvFromArduino()

      print(msg)
      

def communicate(td):
  numLoops = len(td)
  waitingForReply = False

  n = 0
  while n < numLoops:

    teststr = td[n]

    if waitingForReply == False:
      sendToArduino(teststr)
      print("Sent from PC -- ",str(teststr))
      waitingForReply = True

    if waitingForReply == True:

      while ser.inWaiting() == 0:
        pass
        
      dataRecvd = recvFromArduino()
      print("Reply Received: ",dataRecvd)
      n += 1
      waitingForReply = False

      print("===========")

    time.sleep(5)
  # Define callback.
  def my_data_received_callback(xbee_message):
      address = xbee_message.remote_device.get_64bit_addr()
      data = xbee_message.data.decode("utf8")
      print("Received data from %s: %s" % (address, data))

import serial
import time
if __name__ == "__main__":
  # NOTE the user must ensure that the serial port and baudrate are correct
  serPort = "/dev/cu.usbserial-DN02MUUN" #raw_input("Please enter the Serial port: ")
  baudRate = 9600 #input("Please enter the Baudrate: ")
  ser = serial.Serial(serPort, baudRate)
  print("Serial port ",serPort," opened  Baudrate ",str(baudRate))

  startMarker = 60
  endMarker = 62
  input("Turn on sensors?")
  #TODO: Implement a send/rec signal to turn sat online
  sendToArduino("1")
  onlineResponse = recvFromArduino()
  if(onlineResponse == "Satallite is ready"):
    print(onlineResponse)
    print(recvFromArduino())
    print(recvFromArduino())
    print("==================")
    input("Launch it?")
    sendToArduino("1")
    print(recvFromArduino())
    print("==================")
    ser.flushInput()
    ser.flushOutput()
    with open('data.csv', 'w+') as the_file:
      the_file.write("Timestamp (ms),innerAnalogTemp,outerAnalogTemp,pressure,altitude,AccX,AccY,AccZ,innerDigitalTemp\n")
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
  

  ser.close

