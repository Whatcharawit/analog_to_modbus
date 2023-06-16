#include <Arduino.h>
#include <ModbusMaster.h>
#include <HardwareSerial.h>

#define mbEnable PB12

#define A1_PIN PA7
#define A2_PIN PA6
#define A3_PIN PA5
#define A4_PIN PA4
#define A5_PIN PB0
#define A6_PIN PB1

#define min_out 54
#define max_out 175

int slaveID = 1;

float Wind_Speed;
float Wind_Direction;
float Vertical_Wind_Direction;
float X_Wind_Speed;
float Y_Wind_Speed;
float Z_wind_Speed;

int map_Wind_Speed;
int map_Wind_Direction;
int map_Vertivcal_Wind_Direction;
int map_X_Wind_Speed;
int map_Y_Wind_Speed;
int map_Z_Wind_Speed;

int analog_renge = 255;

void preTransmission();
void postTransmission();