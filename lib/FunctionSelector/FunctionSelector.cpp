#include <FunctionSelector.h>

#define DIAL_RADIUS 200 // Should be even
#define SELECTOR_SIZE 152

struct point_t
{
    int32_t x;
    int32_t y;
};

FunctionSelector::FunctionSelector(TFT_eSPI &display) {
  this->_display = &display;
  this->_selectorSize = SELECTOR_SIZE;
}

void FunctionSelector::begin() {
    _selectorSprite = new TFT_eSprite(_display);
    _selectorSprite->createSprite(SELECTOR_SIZE, DIAL_RADIUS);
    _selectorSprite->fillSprite(TFT_GREEN);
}

void FunctionSelector::drawSelector(int32_t x, int32_t y) {
    drawDial();
    _selectorSprite->drawRect(0, 0, SELECTOR_SIZE, DIAL_RADIUS, TFT_WHITE);
    _selectorSprite->pushSprite(x, y);
}

void FunctionSelector::drawDial() {
    int r1 = 60; // Radius to markers
    int r2 = 85; // Radius to labels (80)
    double rad = 0.01745;
    point_t dial_center = {DIAL_RADIUS / 2, DIAL_RADIUS / 2};

    _selectorSprite->fillSprite(TFT_BLACK); // Clear the dial background rectangle
    _selectorSprite->setTextDatum(MC_DATUM);
    _selectorSprite->setTextFont(2); // 2 is medium

    // Center of circle is at 100,100
    // for (int j=0; j<360; j+=30) {
    for (int j = 120; j <= 240; j += 30)
    {
        int x1 = r1 * cos(rad * j) + dial_center.x;
        int y1 = r1 * sin(rad * j) + dial_center.y;

        int x2 = r2 * cos(rad * j) + dial_center.x;
        int y2 = r2 * sin(rad * j) + dial_center.y;

        // Markers are 5px diameter filled circles
        switch (j)
        {
        case 240:
            _selectorSprite->fillCircle(x1, y1, 5, TFT_YELLOW);
            _selectorSprite->drawString("ALT", x2, y2); // ALT
            break;
        case 210:
            _selectorSprite->fillCircle(x1, y1, 5, TFT_YELLOW);
            _selectorSprite->drawString("VS", x2, y2); // VS
            break;
        case 180:
            _selectorSprite->fillCircle(x1, y1, 5, TFT_YELLOW);
            _selectorSprite->drawString("HDG", x2, y2);
            break;
        case 150:
            _selectorSprite->fillCircle(x1, y1, 5, TFT_YELLOW);
            _selectorSprite->drawString("CRS", x2, y2);
            break;
        case 120:
            _selectorSprite->fillCircle(x1, y1, 5, TFT_YELLOW);
            _selectorSprite->drawString("IAS", x2, y2);
            break;
        }
    }

    _selectorSprite->setPivot(dial_center.x, dial_center.y);
}