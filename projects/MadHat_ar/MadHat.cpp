#include "MadHat.h"

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 7

CRGB leds[NUM_LEDS];

void MadHat::init() {
    delay(2000);
    _ledStrip.init(7);
}

void MadHat::update() {
    for(int i = 0; i < _ledStrip.getLength(); i++) {
        _ledStrip[i] = CRGB::White;
        _ledStrip.sendFrame();

        delay(80);

        _ledStrip[i] = CRGB::Black;
    }
}

