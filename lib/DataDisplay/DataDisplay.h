#ifndef __DATADISPLAY_H__
#define __DATADISPLAY_H__

#include <Arduino.h>
#include <TFT_eSPI.h>

class DataDisplay
{
    public:
        DataDisplay(TFT_eSPI& display);
        void begin();
        void showDecimalValue(long value, int numDigits, bool leadingZeros = true);
        void showFloatValue(float value, int numDigits, int numDecimals);

    private:
        TFT_eSPI *_display;
        TFT_eSprite* _display_sprite;

};

#endif // __DATADISPLAY_H__