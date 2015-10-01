#pragma once

#include "LedStrip.h"
#include "Light.h"
#include "signal.h"

class MadHat {
public:
    MadHat() {}
    
    void init();
    void update();

private:
    int _lastTime;

    LedStrip _ledStrip;
    Light* _pHeadLight;
    Light* _pEyesLight;

    Lfo _headLfo;
    Lfo _eyesLfo;
};

