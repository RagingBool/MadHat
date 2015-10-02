#pragma once

#include "LedStrip.h"
#include "Light.h"
#include "fx.h"

class MadHat {
public:
    MadHat() {}
    
    void init();
    void update();

private:
    void initMainFx();
    void initEyesFx();

private:
    int _lastTime;

    LedStrip _ledStrip;
    Light* _pMainLight;
    Light* _pEyesLight;

    IFx* _pMainFx;
    IFx* _pEyesFx;
};

