#include "MadHat.h"

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 7
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

void MadHat::init() {
    delay(2000);
    FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void MadHat::update() {
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
        leds[whiteLed] = CRGB::Black;
        FastLED.show();

        delay(80);

        leds[whiteLed] = CRGB::White;
    }
}

