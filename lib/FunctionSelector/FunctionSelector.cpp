#include <FunctionSelector.h>

#define DIAL_RADIUS 200 // Should be even
#define SELECTOR_SIZE 152
#define TM_WIDTH 210
#define TM_HEIGHT 50

// Variables
bool use_random_values = false;

struct point_t
{
    int32_t x;
    int32_t y;
};

FunctionSelector::FunctionSelector(TFT_eSPI &display) {
  this->_display = &display;
  this->_selectorSize = SELECTOR_SIZE;
  this->_dialOffset = display.width() - 25; // Offset from right edge
}

void FunctionSelector::begin() {
    _selectorSprite = new TFT_eSprite(_display);
    _selectorSprite->createSprite(SELECTOR_SIZE, DIAL_RADIUS);
    _selectorSprite->fillSprite(TFT_GREEN);
    _knobSprite = new TFT_eSprite(_display);
    _textArea = new TFT_eSprite(_display);     
}

void FunctionSelector::drawSelector(int32_t x, int32_t y) {
    drawDial();
    setKnob(330);
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

void FunctionSelector::createKnob(int16_t diameter = 100) {
    int32_t r = diameter / 2; // Radius = Diameter/2
    point_t center = {r, r};  // Center

    Serial.println("Creating knob");
    _knobSprite->createSprite(diameter, diameter);
    _knobSprite->fillSprite(TFT_GREEN); // Green will be set as transparent background)

    // Draw Knob
    // Base of knob has a radius that is 10 pixels less than the  total radius
    // The pointer of the knob extends to the radius
    _knobSprite->fillCircle(center.x, center.y, r, TFT_BLACK);          // Knob+Pointer diameter (was  TFT_LIGHTGREY)
    _knobSprite->fillCircle(center.x, center.y, r - 12, TFT_LIGHTGREY); // knob (was TFT_DARKGREY)
    _knobSprite->drawCircle(center.x, center.y, r - 12, TFT_BLACK);     // Border
    _knobSprite->drawCircle(center.x, center.y, r - 16, TFT_BLACK);     // Border

    // Pointer
    _knobSprite->drawWedgeLine(center.x, center.y, center.x, 2, 8, 3, TFT_RED); // ax, ay, bx, by, aw, bw, color
    _knobSprite->fillCircle(center.x, center.y, 3, TFT_BLACK);
}

void FunctionSelector::setKnob(int16_t angle) {
    static int16_t previous_angle;

    if (angle == previous_angle)
        return;

    Serial.printf("Setting knob to angle %d\n", angle);
    previous_angle = angle;

    if (!_knobSprite->created()) {
        createKnob(100);
    }

    // redraw_labels(angle);
    _selectorSprite->setPivot(100, 100);
    _knobSprite->pushRotated(_selectorSprite, angle, TFT_GREEN); // Push/Rotate knob to dial.  Render Green pixels as transparent
    _selectorSprite->pushSprite(_dialOffset, 1);
        
}

void FunctionSelector::updateValue(int selval) {
    switch (selval)
    {
    case 1:
        // showAirspeed(int(APAirspeed));
        break;
    case 2:
        // showHeading(int(APCourse));
        break;
    case 3:
        // showHeading(int(APHeading));
        break;
    case 4:
        // showVspeed(int(APVertSpeed));
        break;
    case 5:
        // showAltitude(int(APAltitude));
        break;
    }
}

void FunctionSelector::updateFunction(int selval) {
    int ival;
    long lval;
    char msgText[24];               // For messages

    ival = 180 + (selval * 30); // The angle to draw the pointer
    switch (selval)
    {
    case 5:
        sprintf(msgText, "Altitude");
        showMessage(msgText);
        setKnob(ival);
        updateValue(selval);
        break;

    case 4:
        sprintf(msgText, "Vertical Speed");
        showMessage(msgText);
        setKnob(ival);
        updateValue(selval);
        break;

    case 3:
        sprintf(msgText, "Heading");
        showMessage(msgText);
        setKnob(ival);
        updateValue(selval);
        break;

    case 2:
        sprintf(msgText, "Course");
        showMessage(msgText);
        setKnob(ival);
        updateValue(selval);
        break;

    case 1:
        sprintf(msgText, "Air Speed");
        showMessage(msgText);
        setKnob(ival);
        updateValue(selval);
        break;

    default:
        sprintf(msgText, "INVALID: %d", selval);
        showMessage(msgText);
    }
}

void FunctionSelector::showMessage(char *message)
{
    char message2[40];
    point_t msgdisp_loc = {1, 1};

    if (!_textArea->created()) {
        _textArea->createSprite(TM_WIDTH, TM_HEIGHT);
    }

    _textArea->fillSprite(TFT_BLACK);
    _textArea->setTextDatum(MC_DATUM); // MC_DATUM=Middle-Center
    _textArea->setTextColor(TFT_WHITE);
    _textArea->setTextFont(4); // 4
    _textArea->drawString(message, TM_WIDTH / 2, TM_HEIGHT / 2);
    _textArea->drawRect(1, 1, TM_WIDTH-1, TM_HEIGHT-1, TFT_WHITE);
    _textArea->pushSprite(0, 0); // Replace 0,0 with your desired location
}

