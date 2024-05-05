//MULTIPLE VL53L0X Using I2C

// This Script requires connection of XSHUT Pin as it is important to Shutdown the Tof for assigning Address 

/*
   ‎April ‎22, ‎2024 
   Created by Ashutosh Singh 
 */

// Include the library for VL53L0X
#include "Adafruit_VL53L0X.h"

// Define the addresses for each sensor
#define VL53L0X_ADDRESS_1 0x30
#define VL53L0X_ADDRESS_2 0x31
#define VL53L0X_ADDRESS_3 0x32

// Define the XSHUT pin for each sensor
#define XSHUT_1 2
#define XSHUT_2 3
#define XSHUT_3 4

// Create an instance for each sensor
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// Create a variable to hold the measurement for each sensor
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

void setup() {
  // Begin serial communication at 115200 baud rate
  Serial.begin(115200);

  // Wait until the serial port is open
  while(!Serial){
    delay(1);
  }

  // Set the XSHUT pins as output
  pinMode(XSHUT_1,OUTPUT);
  pinMode(XSHUT_2,OUTPUT);
  pinMode(XSHUT_3,OUTPUT);

  // Shutdown all sensors
  digitalWrite(XSHUT_1, LOW);
  digitalWrite(XSHUT_2, LOW);
  digitalWrite(XSHUT_3, LOW);
  delay(10);

  // Turn on all sensors
  digitalWrite(XSHUT_1, HIGH);
  digitalWrite(XSHUT_2, HIGH);
  digitalWrite(XSHUT_3, HIGH);
  delay(10);

  // Turn on only the first sensor
  digitalWrite(XSHUT_1, HIGH);
  digitalWrite(XSHUT_2, LOW);
  digitalWrite(XSHUT_3, LOW);

  // Initialize the first sensor
  if(!lox1.begin(VL53L0X_ADDRESS_1)){
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // Turn on only the second sensor
  digitalWrite(XSHUT_2, HIGH);
  digitalWrite(XSHUT_3, LOW);

  // Initialize the second sensor
  if(!lox2.begin(VL53L0X_ADDRESS_2)){
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  delay(10);

  // Turn on the third sensor
  digitalWrite(XSHUT_3, HIGH);

  // Initialize the third sensor
  if(!lox3.begin(VL53L0X_ADDRESS_3)){
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
  delay(10);
}

void loop() {
  // Perform a ranging test on each sensor
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  lox3.rangingTest(&measure3, false);

  // Print the range in millimeters from each sensor
  Serial.print(measure1.RangeMilliMeter);
  Serial.print(" ");
  Serial.print(measure2.RangeMilliMeter);
  Serial.print(" ");
  Serial.print(measure3.RangeMilliMeter);
  Serial.println();
}
