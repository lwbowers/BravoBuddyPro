#include <Arduino.h>
#include <TFT_eSPI.h>
#include <FunctionSelector.h>

TFT_eSPI tft = TFT_eSPI();
FunctionSelector selector = FunctionSelector(tft);

// CYD_DigitalClock myClock = CYD_DigitalClock(tft);

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  Serial.printf("width: %d, height: %d\n", tft.width(), tft.height());

  selector.begin();
  selector.drawSelector(10,10);
}

void loop() {
  // put your main code here, to run repeatedly:
}
