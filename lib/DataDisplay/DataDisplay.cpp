#include <DataDisplay.h>

DataDisplay::DataDisplay(TFT_eSPI& display) {
    this->_display = &display;
}

void DataDisplay::begin() {
    _display_sprite = new TFT_eSprite(_display);
    _display_sprite->createSprite(212, 60);
    _display_sprite->fillSprite(TFT_BLACK);
}

void DataDisplay::showDecimalValue(long value, int numDigits, bool leadingZeros) {
    char buf[10];
    if (leadingZeros) {
        snprintf(buf, sizeof(buf), "%0*d", numDigits, value);
    } else {
        snprintf(buf, sizeof(buf), "%*d", numDigits, value);
    }
    
    _display_sprite->fillSprite(TFT_BLACK);
    _display_sprite->drawRect(0, 0, 212, 60, TFT_WHITE);
    _display_sprite->setTextColor(TFT_DARKGREEN);
    _display_sprite->setTextDatum(CC_DATUM);
    _display_sprite->setTextFont(7);
    _display_sprite->drawString(buf, 106, 30);
    _display_sprite->pushSprite(0, 75);
    
}
