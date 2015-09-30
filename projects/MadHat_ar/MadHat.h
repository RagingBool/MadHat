#pragma once

#include "LedStrip.h"
#include "Light.h"

class MadHat {
public:
    MadHat() {}
    
    void init();
    void update();

private:
    LedStrip _ledStrip;
    Light* _pHeadLight;
    Light* _pEyesLight;
    float _headHue;
    float _eyesHue;
};

