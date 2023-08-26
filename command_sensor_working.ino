#include <Wire.h>

const int ledPin = 13;    //output led
const int IR_sensor= 2;   //input IR-sensor value

const int touch_sensor= 3;    //input Touch sensor value

const int trigPin = 4;      // input Ultrasonic sensor 
const int echoPin = 5;
long duration;
int distance; 

const int soundSensorPin = A0;

const int fire_sensor= 6;
const int LDR_sensor= 7;

const int pulsePin = A7; 

#define ADXL345_ADDRESS 0x53
#define SDA_PIN A4
#define SCL_PIN A5

void setup() {
  Wire.begin();
  pinMode(ledPin, OUTPUT);
  pinMode(IR_sensor, INPUT);
  pinMode(touch_sensor, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(soundSensorPin, INPUT);
  pinMode(fire_sensor, INPUT);
  pinMode(LDR_sensor, INPUT);
  // Set ADXL345 measurement mode
  Wire.beginTransmission(ADXL345_ADDRESS);
  Wire.write(0x2D); // Power control register
  Wire.write(8);    // Enable measurement mode (Bit 3 HIGH)
  Wire.endTransmission();
  Serial.begin(115200);
}


void loop() {
    char command = Serial.read();
    if (command == '1') {
      int IRValue = digitalRead(IR_sensor);
      if(IRValue == 1)
      {
        digitalWrite(13,HIGH);
        Serial.println("FAR");
      }
      else
      {
        digitalWrite(13,LOW);
        Serial.println("NEAR");
      }
      
    }else if (command == '2') {
      int touchValue = digitalRead(touch_sensor);
      if(touchValue == 1)
      {
        digitalWrite(13,HIGH);
        Serial.println("high");
      }
      else
      {
        digitalWrite(13,LOW);
        Serial.println("low");
      }
    }else if (command == '3'){
              // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(0.02);

        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(0.2);
        digitalWrite(trigPin, LOW);

        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);

        // Calculating the distance
        distance= duration*0.034/2;
        // Prints the distance on the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(distance);
    }else if (command == '4'){
        int soundValue = analogRead(soundSensorPin);
        if(soundValue < 600)
      { 
        digitalWrite(13,HIGH);
        Serial.println("SOUND ON"); 
        Serial.println(soundValue);
      }
      else
      {
        digitalWrite(13,LOW);
        Serial.println("SOUND OFF");
        Serial.println(soundValue);
  
      }
    }else if (command == '5'){
        int TempValue = digitalRead(fire_sensor);
        if(TempValue == LOW)
      {
        
        digitalWrite(13,HIGH);
        Serial.println("IT'S FIRE NOW!..."); 
      }
      else
      {
        digitalWrite(13,LOW);
        Serial.println("There is no fire. ");  
      }      
    }
    else if (command == '6'){
        int LDRValue = digitalRead(LDR_sensor);
        if(LDRValue == LOW)
      {
        digitalWrite(13,LOW);
        Serial.println("LIGHT SOURCE IS HERE..."); 
        Serial.println(LDRValue);
 
      }
      else
      {
        digitalWrite(13,HIGH);
        Serial.println("IT'S DARK HERE... ");
        Serial.println(LDRValue);
  
      }      
    }else if (command == '7'){
        int rawValue = analogRead(pulsePin); // Read the raw analog value from the Pulse Sensor
        int heartRate = map(rawValue, 0, 1023, 0, 180);
        Serial.print("Heart rate raw value: ");
        Serial.println(heartRate);
    }
    else if (command == '8'){
       int16_t x, y, z;
  
        // Read accelerometer data
        Wire.beginTransmission(ADXL345_ADDRESS);
        Wire.write(0x32); // Start reading from register 0x32 (X0)
        Wire.endTransmission(false);
        Wire.requestFrom(ADXL345_ADDRESS, 6, true); // Request 6 bytes (2 bytes for each axis)
        
        // Read the 3-axis data
        x = Wire.read() | (Wire.read() << 8);
        y = Wire.read() | (Wire.read() << 8);
        z = Wire.read() | (Wire.read() << 8);
        
        // Display the X, Y, and Z axis readings
        Serial.print("X: "); Serial.print(x); Serial.print("\t");
        Serial.print("Y: "); Serial.print(y); Serial.print("\t");
        Serial.print("Z: "); Serial.print(z); Serial.println();
    }
 else {
      // Invalid command
      // You can add additional handling here if needed
    }
  }



