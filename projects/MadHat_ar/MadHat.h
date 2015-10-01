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
    void initHeadFx();
    void initEyesFx();

private:
    int _lastTime;

    LedStrip _ledStrip;
    Light* _pHeadLight;
    Light* _pEyesLight;

    IFx* _pHeadFx;
    IFx* _pEyesFx;
};

