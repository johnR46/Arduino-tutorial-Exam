#include <IFTTTMaker.h>

/*******************************************************************
    Trigger event at end of the setup
 *                                                                 *
    adapted by Brian Lough
 *******************************************************************/


#include <WiFi.h>
#include <WiFiClientSecure.h>

//------- Replace the following! ------
char ssid[] = "kidbright";       // your network SSID (name)
char password[] = "12345678";  // your network key
#define KEY "cyMT9Jk5fYrCpb5VZb9aYt"   // Get it from this page https://ifttt.com/services/maker/settings




WiFiClientSecure client;
IFTTTMaker ifttt(KEY, client);

void setup() {

  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  pinMode(23, INPUT_PULLUP);

}

void loop() {
  int ChkStatus;
  if (digitalRead(23) == 0) {
    Serial.print("pin 23 Trigger ...");
    ChkStatus = ifttt.triggerEvent("A");
    if (ChkStatus == 0) {
      Serial.println("> Succooessfully Sent");


    }
    else Serial.println("> Successfully Failed!");
    delay(200);

  }
}
//
