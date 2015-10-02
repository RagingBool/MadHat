#include "MadHat.h"

#include <Arduino.h>
#include <FastLED.h>

void MadHat::init() {
    delay(2000);
    _ledStrip.init(14);
    Light testLight(_ledStrip, 1);

    initLeds();
    initMainFx();
    initEyesFx();

    _lastTime = millis();
}

void MadHat::initLeds() {
    switch(_device) {
        case MAD_HAT: {
            int mainLeds[] = { 0, 1, 2, 3, 5, 7, 8, 9 };
            _pMainLight = new Light(_ledStrip, mainLeds, 8);
            int eyesLeds[] = { 4, 6 };
            _pEyesLight = new Light(_ledStrip, eyesLeds, 2);
        } break;
        case GOBLIN: {
            int mainLeds[] = { 0, 1, 2, 4, 3, 5 };
            _pMainLight = new Light(_ledStrip, mainLeds, 6);
            int eyesLeds[] = { 6, 7, 8, 9 };
            _pEyesLight = new Light(_ledStrip, eyesLeds, 4);
        } break;
        case DISCO_JACKET: {
            int mainLeds[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
            _pMainLight = new Light(_ledStrip, mainLeds, 14);
            _pEyesLight = new Light(_ledStrip, 0, 0);
        } break;
    }
}

void MadHat::initMainFx() {
    float lowIntensity = 0.4f;
    float normalIntensity = 0.6f;
    float highIntensity = 1.f;
    float normalSaturation = 0.7f;
    float highSaturation = 1.0f;
    int maxChasingLights;
    int maxChasingLightsSwarm;
    
    switch(_device) {
        case MAD_HAT: {
            maxChasingLights = 3;
            maxChasingLightsSwarm = 5;
        } break;
        case GOBLIN: {
            maxChasingLights = 2;
            maxChasingLightsSwarm = 4;
        } break;
        case DISCO_JACKET: {
            lowIntensity = 0.3f;
            normalIntensity = 0.5f;
            maxChasingLights = 4;
            maxChasingLightsSwarm = 7;
        } break;
    }

    // Populate main effects
    IFx** ppMainFxs = new IFx*[20];
    int numMainFx = 0;
    ppMainFxs[numMainFx++] = new ColorCycleFx(_pMainLight, 1000, normalSaturation, lowIntensity);
    ppMainFxs[numMainFx++] = new ChasingLightsFx(_pMainLight, 100, 1, maxChasingLights, highSaturation, highIntensity);
    ppMainFxs[numMainFx++] = new ChasingLightsFx(_pMainLight, 350, maxChasingLights + 1, maxChasingLightsSwarm, normalSaturation, normalIntensity);
    IFx* pSwtichingFx = new SwitchingFx(ppMainFxs, numMainFx, 5000, 10000);

    // Create the top-level effects
    IFx* pCrazyColors = new CrazyLightsFx(_pMainLight, highSaturation, normalIntensity);
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

