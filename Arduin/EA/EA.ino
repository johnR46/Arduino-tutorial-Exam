
#define pwma 255
#define ENA 13
#define IN1 12
#define IN2 14
#define IN3 27
#define IN4 26
#define ENB 25
#define pwmb 255
char   Rxapp;
// pwm Lowlevel
int freq = 5000;
int ledChannel = 0;
int ledChannel2 = 1;
int resolution = 8;
// ble
#include "BLE.h"
BLE ble("BLE Basic");
n


void forward() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  ledcWrite(0, pwma);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  ledcWrite(1, pwmb);

}
void reward() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  ledcWrite(0, pwma);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  ledcWrite(1, pwmb);
}
void left() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  ledcWrite(0, pwma);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  ledcWrite(1, pwmb);
}
void right() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  ledcWrite(0, pwma);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  ledcWrite(1, pwmb);
}
void stopm() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  ledcWrite(0, pwma);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  ledcWrite(1, pwmb);
}




void setup() {

  //  Bluetooth
  Serial.begin(115200);
  ble.begin();
   
  ble.on(READ, [](int service_uuid, int char_uuid) {
    Serial.println("Event: READ");
    Serial.print("Service UUID: 0x");
    Serial.println(service_uuid, HEX);
    Serial.print("Characteristic UUID: 0x");
    Serial.println(char_uuid, HEX);
  
    ble.reply("OK !");
  });
  
  ble.on(WRITE, [](int service_uuid, int char_uuid) {
    Serial.println("Event: WRITE");
    Serial.print("Service UUID: 0x");
    Serial.println(service_uuid, HEX);
    Serial.print("Characteristic UUID: 0x");
    Serial.println(char_uuid, HEX);
    Serial.print("Data: ");
    char *data = ble.data();
    for (int i=0;data[i]!=0;i++) {
        Serial.print("0x");
        if (data[i] < 0x10) Serial.print("0");
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
  });
  BLEService *service = new BLEService(0xFF);
  service->addCharacteristic(0xFF01);
  service->addCharacteristic(0xFF02);
  ble.addService(service);

  // Motor
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // pwm
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(13, ledChannel);
  ledcAttachPin(25, ledChannel2);


}

void loop() {
  if (Serial.avnailable()) {
    Rxapp = Serial.read();
    Serial.println(Rxapp);

  }

  if (Rxapp == 'A') {
    forward();
  }

  if (Rxapp == 'B') {
    reward();
  }

  if (Rxapp == 'C') {
    left();
  }

  if (Rxapp == 'D') {
    right();
  }
  else {
    stopm();
  }
}
