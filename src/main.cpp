#include <Arduino.h>
#include <TFT_eSPI.h>
#include <FunctionSelector.h>
#include <DataDisplay.h>

TFT_eSPI tft = TFT_eSPI();
FunctionSelector selector = FunctionSelector(tft);
DataDisplay dataDisplay = DataDisplay(tft);

// CYD_DigitalClock myClock = CYD_DigitalClock(tft);

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  Serial.printf("width: %d, height: %d\n", tft.width(), tft.height());

  selector.begin();
  selector.drawSelector(10,10);

  dataDisplay.begin();
  dataDisplay.showDecimalValue(0, 5);
}

void loop() {
  static int old_selectorPosition = 0;
  static unsigned long updateFunctionTrigger = 0;

  long value;
  int selectorPosition;

  if (millis() >= updateFunctionTrigger) {
    updateFunctionTrigger = millis() + 5000;
    selectorPosition = random(1,6);
    if (selectorPosition != old_selectorPosition) {
        old_selectorPosition = selectorPosition;
        selector.updateFunction(selectorPosition);
    }
  }

  switch (selectorPosition) {
    case 1:
      // Airspeed
      value = random(80,280);
      dataDisplay.showDecimalValue(value, 3, false);
      break;
    case 2:
      // Course
      value = random(1,360);
      dataDisplay.showDecimalValue(value, 3);
      break;
    case 3:
      // Heading
      value = random(0,359);
      dataDisplay.showDecimalValue(value, 3);

      break;
    case 4:
      // Vertical Speed
      value = random(-5,5);
      dataDisplay.showDecimalValue(value, 2, false);
      break;
    case 5:
      // Altitude
      value = random(1200,45000);
      dataDisplay.showDecimalValue(value, 6, false);
      break;
    default:
      value = 0;
  }
  
  delay(1000);

}
