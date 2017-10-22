#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT11

const char* ssid = "SunLuCiFer";
const char* password = "sun56789";
String apiKey = "63TZO6HHQ8EEZ2S5";
const char* server = "api.thingspeak.com";
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;


void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println(); Serial.println();
  Serial.print("Connecting to "); Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  { delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  dht.begin();
}


void loop() {
  Serial.println("------------------------------------");
  Serial.println("Requesting temperatures...");
  float cTemp = dht.readTemperature();
  float Humid = dht.readHumidity();
//  if (isnan(h) || isnan(t) || isnan(f)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
  Serial.print("Temperature is: "); Serial.println(cTemp, 2);
  Serial.print("Humidity is: "); Serial.println(Humid, 2);
  if (client.connect(server, 80))
  { String postStr = apiKey;
    postStr += "&field1="; // Fields 1
    postStr += String(cTemp);
    postStr += "&field2="; // Fields 2
    postStr += String(Humid);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("Waiting...");
  delay(20000); // thingspeak needs minimum 15 sec delay between updates
}
