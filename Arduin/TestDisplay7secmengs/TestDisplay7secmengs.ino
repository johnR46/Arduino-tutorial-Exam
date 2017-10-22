#include "LedControl.h"


LedControl lc = LedControl(5, 2, 4, 1); // 5-DataIn, 2-CLK, 4-LOAD dht11 DHT;


void setup() {
  Serial.begin(115200);
  lc.shutdown(0, false);
  lc.setIntensity(0, 12);
  lc.clearDisplay(0);

}

void loop() {



  lc.setDigit(0, 7, 11, false);
  lc.setDigit(0, 6, 5 , false);
  lc.setDigit(0, 5, 8, false);
  lc.setDigit(0, 4, 1, false);
  lc.setDigit(0, 3, 4 , false);
  lc.setDigit(0, 2, 8 , false);
  lc.setDigit(0, 1, 2 , false);
  lc.setDigit(0, 0, 4 , false);


  delay(2000);

}
