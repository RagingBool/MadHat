#include "LedStrip.h"

#define DATA_PIN 3

LedStrip::~LedStrip() {
    if(_data != 0) {
        delete _data;
        _length = 0;
        _data = 0;
    }
}

void LedStrip::init(int length) {
    _length = length;
    _data = new CRGB[length];
    FastLED.addLeds<WS2811, DATA_PIN, RGB>(_data, length);

    for(int i = 0; i < _length; i++) {
        _data[i] = CRGB::Black;
    }
}

void LedStrip::sendFrame() {
    FastLED.show();
}

