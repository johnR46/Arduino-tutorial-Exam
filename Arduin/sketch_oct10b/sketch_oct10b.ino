#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12); // RX, TX
#define PWM1 255
#define PWM2 255
#define PWM3 255
char ch;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT); // pwm  1
  pinMode(4, OUTPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); // pwm 2
  pinMode(7, OUTPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT); // pwm 3
  pinMode(10, OUTPUT);

  // blue
  mySerial.begin(9600);


}

void loop() {
  if (mySerial.available() > 0) {
    ch = mySerial.read();
    Serial.println(ch);
  }

  if (ch == 'F') {
    Forward();
  }
  if (ch == 'B') {
    Backward();
  }
  if (ch == 'L') {
    Left();
  }
  if (ch == 'R') {
    Right();
  }
  if (ch == 'S') {
    Stop();
  }



}
void Stop() {
  digitalWrite(2, 0);
  digitalWrite(4, 0);
  analogWrite(3, 0);

  digitalWrite(5, 0);
  digitalWrite(7, 0);
  analogWrite(6, 0);

  digitalWrite(8, 0);
  digitalWrite(10, 0);
  analogWrite(9, 0);


}
void Left() {
  digitalWrite(2, 0);
  digitalWrite(4, 1);
  analogWrite(3, PWM1);

  digitalWrite(5, 1);
  digitalWrite(7, 0);
  analogWrite(6, PWM2);

  digitalWrite(8, 1);
  digitalWrite(10, 0);
  analogWrite(9, PWM3);

}
void Right() {
  digitalWrite(2, 1);
  digitalWrite(4, 0);
  analogWrite(3, PWM1);

  digitalWrite(5, 0);
  digitalWrite(7, 1);
  analogWrite(6, PWM2);

  digitalWrite(8, 0);
  digitalWrite(10, 1);
  analogWrite(9, PWM3);

}
void Forward() {
  Serial.println('F');
  digitalWrite(2, 0);
  digitalWrite(4, 1);
  analogWrite(3, PWM1);

  digitalWrite(5, 0);
  digitalWrite(7, 1);
  analogWrite(6, PWM2);

  digitalWrite(8, 0);
  digitalWrite(10, 0);
  analogWrite(9, PWM3);

}
void Backward() {
  digitalWrite(2, 1);
  digitalWrite(4, 0);
  analogWrite(3, PWM1);

  digitalWrite(5, 1);
  digitalWrite(7, 0);
  analogWrite(6, PWM2);

  digitalWrite(8, 0);
  digitalWrite(10, 0);
  analogWrite(9, PWM3);

}

