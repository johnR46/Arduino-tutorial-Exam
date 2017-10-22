#include <AntoIO.h>
#define LED1 2

const char* ssid = "PLOY";
const char* pass = "12345678"; 
const char *user = "johnNonphala";
const char *token = "6BnomeaX2JaOXzl5B9xxNEN5ekqOal38g3MT3EF0";
 const char *thing = "test_esp32";
const char *channel_D2 = "LED1"; 


/* create AntoIO instance */
AntoIO anto(user, token, thing);

void setup() {
  pinMode(LED1, OUTPUT);

  Serial.begin(9600);
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");

  while (!anto.wifi.begin(ssid, pass));
  Serial.println("\nConnected, trying to connect to broker...");

  while (!anto.mqtt.connect(user, token, true));
  Serial.println("\nConnected");

  /* change "digital-channel" to your channel in switch type */
  anto.mqtt.sub(channel_D2);
}

void loop() {
  anto.mqtt.loop();
  /*
     for proper functionality,
     10-second delay should be added after loop()
  */
  delay(10);
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();

  if (payload.toInt() == 1) {
    digitalWrite(LED1, HIGH);
    Serial.println("HIGH");
  } else {
    digitalWrite(LED1, LOW);
    Serial.println("LOW");
  }
}
