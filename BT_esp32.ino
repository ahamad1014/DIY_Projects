#include <BluetoothSerial.h>

#define L1 13
#define L2 12
#define R1 15
#define R2 2

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");  // Bluetooth device name
  Serial.println("Bluetooth Device is ready to pair");
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  if(SerialBT.connected()){
    Serial.write("BT_Connected");
  }
}

void loop() {
  if (Serial.available()) {
    char data = Serial.read();
    SerialBT.write(data);  // Send data over Bluetooth
  }

  if (SerialBT.available()) {
    char btl = SerialBT.read();   // Print received data to Serial Monitor
    switch(btl)
  {
    case 'F': 
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(R1,HIGH);
      digitalWrite(R2,LOW);
      Serial.println("front");
      break;
    case 'B': 
      digitalWrite(L1,LOW);
      digitalWrite(L2,HIGH);
      digitalWrite(R1,LOW);
      digitalWrite(R2,HIGH);
      Serial.println("back");
      break;
    case 'L': 
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(R1,LOW);
      digitalWrite(R2,HIGH);
      Serial.println("left");
      break;
    case 'R': 
      digitalWrite(L1,LOW);
      digitalWrite(L2,HIGH);
      digitalWrite(R1,HIGH);
      digitalWrite(R2,LOW);
      Serial.println("right");
      break;
    default:
      digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(R1,LOW);
      digitalWrite(R2,LOW);
      Serial.println("stop");
  }
  delay(10);
  }

}
