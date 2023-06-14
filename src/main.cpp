#include "config.h"

HardwareSerial mySerial(USART1);
HardwareSerial mbSerial(USART3);
ModbusMaster node;

void setup() 
{
  mySerial.begin(115200); 
  mbSerial.begin(9600);
  mySerial.println("Hello Analog");

  pinMode(mbEnable, OUTPUT);
  node.begin(slaveID, mbSerial);

  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() 
{
  uint8_t result = node.readHoldingRegisters(32, 2);

  if(result == node.ku8MBSuccess)
  {
    humidity = node.getResponseBuffer(0)/10;
    temp = node.getResponseBuffer(1)/100;
    
    mySerial.print("Humidity : ");
    mySerial.print(humidity);
    mySerial.print("\t%RH : ");
    mySerial.println(temp);
  }
  else
  {
    mySerial.print("Modbus Error: ");
    mySerial.println(result, HEX);
  }
  delay(1000);
}

void preTransmission()
{
  digitalWrite(mbEnable, HIGH);
}

void postTransmission()
{
  digitalWrite(mbEnable, LOW);
}
