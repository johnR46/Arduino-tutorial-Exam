#include <AntoIO.h>
#define LED_D2 2
#define LED_D3 15
#define LED_D4 4
#define LED_D5 5
#define Monitor_D23 23
int sts_Monitor_D23;
const char* ssid = "PLOY";
const char* pass = "12345678";
const char *user = "johnAnto";
const char *token = "6BnomeaX2JaOXzl5B9xxNEN5ekqOal38g3MT3EF0";
const char *thing = "test_esp32";
const char *channel_D2 = "LED_D2";
const char *channel_D23 = "SW1";
const char *channel_D3 = "LED_D3";
const char *channel_D4 = "LED_D4";
const char *channel_D5 = "LED_D5";
/* create AntoIO instance */
AntoIO anto(user, token, thing);
void setup() {
  pinMode(LED_D2, OUTPUT);
  pinMode(LED_D3, OUTPUT);
  pinMode(LED_D4, OUTPUT);
  pinMode(LED_D5, OUTPUT);
  pinMode(Monitor_D23, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");
  while (!anto.wifi.begin(ssid, pass));
  Serial.println("-- Connected, trying to connect to broker...");
  while (!anto.mqtt.connect(user, token, true));
  Serial.println("-- Connected");
  /* change "digital-channel" to your channel in switch type */
  anto.mqtt.sub(channel_D2);
  anto.mqtt.sub(channel_D3);
  anto.mqtt.sub(channel_D4);
  anto.mqtt.sub(channel_D5);
  anto.mqtt.sub(channel_D23);

}
void loop() {
  anto.mqtt.loop();
  /*
    for proper functionality,
    10-second delay should be added after loop()
  */
  delay(10);
  if (sts_Monitor_D23 != digitalRead(Monitor_D23))
  { sts_Monitor_D23 = digitalRead(Monitor_D23);
    anto.mqtt.pub(channel_D23, sts_Monitor_D23);
    Serial.print(" Status D23 = ");
    Serial.println(sts_Monitor_D23);
    delay(10);
  }
}
void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
  if (topic.indexOf(channel_D2) != -1)
    if (payload.toInt() == 1) {
      digitalWrite(LED_D2, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(LED_D2, LOW);
      Serial.println("LOW");
    };
    
  if (topic.indexOf(channel_D3) != -1)
    if (payload.toInt() == 1) {
      digitalWrite(LED_D3, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(LED_D3, LOW);
      Serial.println("LOW");
    };
  if (topic.indexOf(channel_D4) != -1)
    if (payload.toInt() == 1) {
      digitalWrite(LED_D4, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(LED_D4, LOW);
      Serial.println("LOW");
    };
  if (topic.indexOf(channel_D5) != -1)
    if (payload.toInt() == 1) {
      digitalWrite(LED_D5, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(LED_D5, LOW);
      Serial.println("LOW");
    };

}

