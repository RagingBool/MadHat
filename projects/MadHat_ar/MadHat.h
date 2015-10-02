#pragma once

#include "LedStrip.h"
#include "Light.h"
#include "fx.h"

class MadHat {
public:
    enum Device {
        MAD_HAT,
        GOBLIN,
        DISCO_JACKET
    };

    MadHat(Device device) : _device(device) {}
    
    void init();
    void update();

private:
    void initLeds();
    void initMainFx();
    void initEyesFx();

private:
    Device _device;
    
    int _lastTime;

    LedStrip _ledStrip;
    Light* _pMainLight;
    Light* _pEyesLight;

    IFx* _pMainFx;
    IFx* _pEyesFx;
};

