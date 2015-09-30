#include "MadHat.h"

#include <Arduino.h>
#include <FastLED.h>

void MadHat::init() {
    delay(2000);
    _ledStrip.init(7);
    Light testLight(_ledStrip, 1);

    int headLeds[] = { 0, 1, 2 };
    _pHeadLight = new Light(_ledStrip, headLeds, 3);
    int eyesLeds[] = { 3, 4, 5, 6 };
    _pEyesLight = new Light(_ledStrip, eyesLeds, 4);
    
    _headHue = 0.f;
    _eyesHue = 0.f;
}

void MadHat::update() {
    _pHeadLight -> setHsi(_headHue, .7f, 1.f);
    _pEyesLight -> setHsi(_eyesHue, 1.f, .6f);

    _headHue += 0.005f;
    _eyesHue += 0.015f;

    _ledStrip.sendFrame();

    delay(20);
}

