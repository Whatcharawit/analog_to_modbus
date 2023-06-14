#include <Arduino.h>
#include <ModbusMaster.h>
#include <HardwareSerial.h>

#define mbEnable PB12
int slaveID = 2;

float humidity;
float temp;

void preTransmission();
void postTransmission();