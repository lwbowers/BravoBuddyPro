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
  void updateFunction(int selval);

private:
  TFT_eSPI *_display;
  TFT_eSprite* _selectorSprite;
  TFT_eSprite* _knobSprite;
  TFT_eSprite* _textArea;

  int16_t _selectorSize;
  int32_t _dialOffset;


  void drawDial();
  void createKnob(int16_t diameter);
  void setKnob(int16_t angle); 
  void updateValue(int selval);
  void showMessage(char *message);
  
};

#endif // __FUNCTIONSELECTOR_H__