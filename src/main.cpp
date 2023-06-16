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

  pinMode(A1_PIN, OUTPUT);
  pinMode(A2_PIN, OUTPUT);
  pinMode(A3_PIN, OUTPUT);
  pinMode(A4_PIN, OUTPUT);
  pinMode(A5_PIN, OUTPUT);
  pinMode(A6_PIN, OUTPUT);

  node.begin(slaveID, mbSerial);

  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() 
{
  uint8_t result = node.readHoldingRegisters(0, 6);

  if(result == node.ku8MBSuccess)
  {
    Wind_Speed = node.getResponseBuffer(0)/10;
    Wind_Direction = node.getResponseBuffer(1)/10;
    Vertical_Wind_Direction = node.getResponseBuffer(2)/10;
    X_Wind_Speed = node.getResponseBuffer(3)/10;
    Y_Wind_Speed = node.getResponseBuffer(4)/10;
    Z_wind_Speed = node.getResponseBuffer(5)/10;

    map_Wind_Speed = map(Wind_Speed, 0.0, 60.0, min_out, max_out);
    map_Wind_Direction = map(Wind_Direction, 0.0, 360, min_out, max_out);
    map_Vertivcal_Wind_Direction = map(Vertical_Wind_Direction, -90, 90, min_out, max_out);
    map_X_Wind_Speed = map(X_Wind_Speed, 0.0, 60.0, min_out, max_out);
    map_Y_Wind_Speed = map(Y_Wind_Speed, 0.0, 60, min_out, max_out);
    map_Y_Wind_Speed = map(Z_wind_Speed, 0.0, 60.0, min_out, max_out);

    mySerial.print("Wind Speed              : ");
    mySerial.println(Wind_Speed);
    mySerial.print("Wind Direction          : ");
    mySerial.println(Wind_Direction);
    mySerial.print("Vertical Wind Direction : ");
    mySerial.println(Vertical_Wind_Direction);
    mySerial.print("X Wind Speed            : ");
    mySerial.println(X_Wind_Speed);
    mySerial.print("Y Wind Speed            : ");
    mySerial.println(Y_Wind_Speed);
    mySerial.print("Z Wind Speed            : ");
    mySerial.println(Z_wind_Speed);
    mySerial.println("-------------------------------------");
  }
  else
  {
    mySerial.print("Modbus Error: ");
    mySerial.println(result, HEX);
  }

  // digitalWrite(A1_PIN, LOW);
  analogWrite(A1_PIN, map_Wind_Speed);
  analogWrite(A2_PIN, map_Wind_Direction);
  analogWrite(A3_PIN, map_Vertivcal_Wind_Direction);
  analogWrite(A4_PIN, map_X_Wind_Speed);
  analogWrite(A5_PIN, map_Y_Wind_Speed);
  analogWrite(A6_PIN, map_Z_Wind_Speed);

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
