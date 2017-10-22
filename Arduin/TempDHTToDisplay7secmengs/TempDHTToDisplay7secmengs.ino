#include "LedControl.h"
#include "DHT.h"

#define DHTPIN 23
#define DHTTYPE DHT11

int Tempp2 = 7, Tempp1 = 6, Tempp0 = 5;
int Humi2 = 4, Humi1 = 3, Humi0 = 2;

LedControl lc = LedControl(5, 2, 4, 1); // 5-DataIn, 2-CLK, 4-LOAD dht11 DHT;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  lc.shutdown(0, false);
  lc.setIntensity(0, 12);
  lc.clearDisplay(0);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  int t = temp * 100;
  int h = humid * 100;

 

 lc.setDigit(0, 7, t / 1000, false);
  lc.setDigit(0, 6, (t / 100) % 10, true);
  lc.setDigit(0, 5, (t % 100) / 10, false);
  lc.setDigit(0, 4, 12, false);
  lc.setDigit(0, 3, h / 1000, false);
  lc.setDigit(0, 2, (h / 100) % 10, true);
  lc.setDigit(0, 1, (h % 100) / 10, false);
 // lc.setRow(0, 0, B00010111);

  delay(2000);
  
}
