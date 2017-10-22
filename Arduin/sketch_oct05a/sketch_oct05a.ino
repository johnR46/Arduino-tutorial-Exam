int freq = 5000;
int ledChannel = 0;
int ledChannel2 = 1;
int resolution = 8;

void setup() {
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(13, ledChannel);
  ledcAttachPin(25, ledChannel2);
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
}
void loop() {
  digitalWrite(12, HIGH);
  digitalWrite(14, LOW);
  ledcWrite(ledChannel, 255);//13 ปรับความเร็วขวา
  digitalWrite(27, 0);
  digitalWrite(26, 1);
  ledcWrite(ledChannel2, 255); // 25 ปรับความเร็วซ้าย

}

