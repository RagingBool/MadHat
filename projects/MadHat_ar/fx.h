#pragma once

#include "Light.h"
#include "signal.h"

class IFx {
public:
    virtual ~IFx() { }

    virtual void reset() = 0;
    virtual void update(int dt_millis) = 0;
};

class ColorCycleFx : public IFx {
public:
    ColorCycleFx(Light* pLight, int period, float saturation, float intensity);
    
    virtual void reset();
    virtual void update(int dt_millis);

private:
    Light* _pLight;
    float _saturation;
    float _intensity;
    
    Lfo _hueLfo;
};

