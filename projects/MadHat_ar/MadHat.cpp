#include "MadHat.h"

#include <Arduino.h>
#include <FastLED.h>

void MadHat::init() {
    delay(2000);
    _ledStrip.init(14);
    Light testLight(_ledStrip, 1);

    
    int mainLeds[] = { 0, 1, 2, 4, 3, 5 };
    _pMainLight = new Light(_ledStrip, mainLeds, 6);
    int eyesLeds[] = { 6, 7, 8, 9 };
    _pEyesLight = new Light(_ledStrip, eyesLeds, 4);
    

    /*
    int mainLeds[] = { 0, 1, 2, 3, 5, 7, 8, 9 };
    _pMainLight = new Light(_ledStrip, mainLeds, 8);
    int eyesLeds[] = { 4, 6 };
    _pEyesLight = new Light(_ledStrip, eyesLeds, 2);
    */

    /*
    int mainLeds[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    _pMainLight = new Light(_ledStrip, mainLeds, 14);
    _pEyesLight = new Light(_ledStrip, 0, 0);
    */
    
    initMainFx();
    initEyesFx();

    _lastTime = millis();
}

void MadHat::initMainFx() {
    IFx* pCrazyColors = new CrazyLightsFx(_pMainLight, 1.f, 0.7f);

    IFx** ppMainFxs = new IFx*[3];
    ppMainFxs[0] = new ColorCycleFx(_pMainLight, 1000, .7f, 0.7f);
    ppMainFxs[1] = new ChasingLightsFx(_pMainLight, 100, 1, 4, 1.f, 1.f);
    ppMainFxs[2] = new ChasingLightsFx(_pMainLight, 350, 5, 8, .7f, .5f);
    IFx* pSwtichingFx = new SwitchingFx(ppMainFxs, 3, 5000, 10000);

    _pMainFx = new InterruptingFx(pSwtichingFx, pCrazyColors, 10000, 20000, 1000, 2000);
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

    _pMainFx -> update(dt);
    _pEyesFx -> update(dt);

    _pMainFx -> render();
    _pEyesFx -> render();
    _ledStrip.sendFrame();

    delay(15);
}

