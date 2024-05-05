// Include the libraries for the VL53L0X and MPU6050 sensors
#include "Adafruit_VL53L0X.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Define the I2C addresses for the VL53L0X sensors
#define VL53L0X_ADDRESS_1 0x30
#define VL53L0X_ADDRESS_2 0x31
#define VL53L0X_ADDRESS_3 0x32

// Define the I2C address for the MPU6050 sensor
#define MPU6050_ADDRESS 0x33

// Variables to store the gyro values
float gyroX, gyroY, gyroZ;

// Define the XSHUT pins for the VL53L0X sensors
#define XSHUT_1 2
#define XSHUT_2 3
#define XSHUT_3 4

// Create an object for the MPU6050 sensor
Adafruit_MPU6050 mpu;

// Create objects for the VL53L0X sensors
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// Variables to hold the measurements from the VL53L0X sensors
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Wait for the serial port to open
  while(!Serial){
    delay(1);
  }

  // Set up the XSHUT pins as outputs
  pinMode(XSHUT_1,OUTPUT);
  pinMode(XSHUT_2,OUTPUT);
  pinMode(XSHUT_3,OUTPUT);

  // Assign addresses to the VL53L0X sensors
  // Shut down all sensors to begin the address assignment process
  digitalWrite(XSHUT_1, LOW);
  digitalWrite(XSHUT_2, LOW);
  digitalWrite(XSHUT_3, LOW);
  delay(10);

  // Turn on all sensors
  digitalWrite(XSHUT_1, HIGH);
  digitalWrite(XSHUT_2, HIGH);
  digitalWrite(XSHUT_3, HIGH);
  delay(10);

  // Initialize each VL53L0X sensor with a unique address
  // Sensor 1
  digitalWrite(XSHUT_1, HIGH);
  digitalWrite(XSHUT_2, LOW);
  digitalWrite(XSHUT_3, LOW);
  if(!lox1.begin(VL53L0X_ADDRESS_1)){
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // Sensor 2
  digitalWrite(XSHUT_2, HIGH);
  if(!lox2.begin(VL53L0X_ADDRESS_2)){
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  delay(10);

  // Sensor 3
  digitalWrite(XSHUT_3, HIGH);
  if(!lox3.begin(VL53L0X_ADDRESS_3)){
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
  delay(10);

  // Initialize the MPU6050 sensor
  if (!mpu.begin(MPU6050_ADDRESS)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // Configure the MPU6050 sensor's gyro range and filter bandwidth
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // Take measurements from each VL53L0X sensor
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  lox3.rangingTest(&measure3, false);

  // Take measurements from the MPU6050 sensor
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  // Print the measurements from the VL53L0X sensors and the gyro Z value from the MPU6050
  Serial.print(measure1.RangeMilliMeter);
  Serial.print(" ");
  Serial.print(measure2.RangeMilliMeter);
  Serial.print(" ");
  Serial.print(measure3.RangeMilliMeter);
  Serial.print(" ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
}
