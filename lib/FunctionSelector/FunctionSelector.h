#ifndef __FUNCTIONSELECTOR_H__
#define __FUNCTIONSELECTOR_H__


#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <TFT_eSPI.h>

class FunctionSelector {
public:
  FunctionSelector(TFT_eSPI &display);
  void begin();
  void drawSelector(int32_t x, int32_t y);

private:
  TFT_eSPI *_display;
  TFT_eSprite* _selectorSprite;
  int16_t _selectorSize;

  void drawDial();
};

#endif // __FUNCTIONSELECTOR_H__