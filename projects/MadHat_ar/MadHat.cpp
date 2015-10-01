#include "MadHat.h"

#include <Arduino.h>
#include <FastLED.h>

void MadHat::init() {
    delay(2000);
    _ledStrip.init(10);
    Light testLight(_ledStrip, 1);

    /*
    int headLeds[] = { 0, 1, 2, 3, 4, 5 };
    _pHeadLight = new Light(_ledStrip, headLeds, 6);
    int eyesLeds[] = { 6, 7, 8, 9 };
    _pEyesLight = new Light(_ledStrip, eyesLeds, 4);*/
    
    int headLeds[] = { 0, 1, 2, 3, 5, 7, 8, 9 };
    _pHeadLight = new Light(_ledStrip, headLeds, 8);
    int eyesLeds[] = { 4, 6 };
    _pEyesLight = new Light(_ledStrip, eyesLeds, 2);

    _pHeadFx = new ColorCycleFx(_pHeadLight, 30000, .7f, 0.7f);
    _pEyesFx = new FadingEyesFx(_pEyesLight, 11000, 1.f, 1.f);

    _lastTime = millis();
}

void MadHat::update() {
    int time = millis();
    int dt = time - _lastTime;
    _lastTime = time;

    _pHeadFx -> update(dt);
    _pEyesFx -> update(dt);

    _ledStrip.sendFrame();

    delay(15);
}

