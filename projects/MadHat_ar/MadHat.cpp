#include "MadHat.h"

#include <Arduino.h>
#include <FastLED.h>

void MadHat::init() {
    delay(2000);
    _ledStrip.init(14);
    Light testLight(_ledStrip, 1);

    
    int headLeds[] = { 0, 1, 2, 3, 4, 5 };
    _pHeadLight = new Light(_ledStrip, headLeds, 6);
    int eyesLeds[] = { 6, 7, 8, 9 };
    _pEyesLight = new Light(_ledStrip, eyesLeds, 4);
    

    /*
    int headLeds[] = { 0, 1, 2, 3, 5, 7, 8, 9 };
    _pHeadLight = new Light(_ledStrip, headLeds, 8);
    int eyesLeds[] = { 4, 6 };
    _pEyesLight = new Light(_ledStrip, eyesLeds, 2);
    */

    /*
    int headLeds[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    _pHeadLight = new Light(_ledStrip, headLeds, 14);
    _pEyesLight = new Light(_ledStrip, 0, 0);
    */
    
    initHeadFx();
    initEyesFx();

    _lastTime = millis();
}

void MadHat::initHeadFx() {
    IFx* pCrazyColors = new CrazyLightsFx(_pHeadLight, 1.f, 0.7f);

    IFx** ppMainFxs = new IFx*[3];
    ppMainFxs[0] = new ColorCycleFx(_pHeadLight, 1000, .7f, 0.7f);
    ppMainFxs[1] = new ChasingLightsFx(_pHeadLight, 100, 1, 4, 1.f, 1.f);
    ppMainFxs[2] = new ChasingLightsFx(_pHeadLight, 350, 5, 8, .7f, .5f);
    IFx* pSwtichingFx = new SwitchingFx(ppMainFxs, 3, 5000, 10000);

    _pHeadFx = new InterruptingFx(pSwtichingFx, pCrazyColors, 10000, 20000, 1000, 2000);
}

void MadHat::initEyesFx() {
    IFx* pFadingEyes = new FadingEyesFx(_pEyesLight, 11000, 1.f, 1.f);
    IFx* pCrazyEyes = new CrazyLightsFx(_pEyesLight, 1.f, 1.f);

    _pEyesFx = new InterruptingFx(pFadingEyes, pCrazyEyes, 20000, 30000, 3000, 5000);
}

void MadHat::update() {
    int time = millis();
    int dt = time - _lastTime;
    _lastTime = time;

    _pHeadFx -> update(dt);
    _pEyesFx -> update(dt);

    _pHeadFx -> render();
    _pEyesFx -> render();
    _ledStrip.sendFrame();

    delay(15);
}

