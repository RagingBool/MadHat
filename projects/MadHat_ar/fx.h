#pragma once

#include "Light.h"
#include "signal.h"

class IFx {
public:
    virtual ~IFx() { }

    virtual void reset() = 0;
    virtual void poke() { }
    virtual void update(int dt_millis) = 0;
    virtual void render() = 0;
};

class ColorCycleFx : public IFx {
public:
    ColorCycleFx(Light* pLight, int period, float saturation, float intensity);
    
    virtual void reset();
    virtual void update(int dt_millis);
    virtual void render();

private:
    Light* _pLight;
    float _saturation;
    float _intensity;
    
    Lfo _hueLfo;
};

class FadingEyesFx : public IFx {
public:
    FadingEyesFx(Light* pLight, int period, float saturation, float maxIntensity);

    virtual void reset();
    virtual void poke();
    virtual void update(int dt_millis);
    virtual void render();

private:
    Light* _pLight;
    float _saturation;
    float _maxIntensity;
    
    float _hue;
    Lfo _fadeLfo;
};

class CrazyLightsFx : public IFx {
public:
    CrazyLightsFx(Light* pLight, float saturation, float intensity);

    virtual void reset();
    virtual void update(int dt_millis);
    virtual void render();

private:
    void nextStep();

private:
    Light* _pLight;
    float _saturation;
    float _intensity;

    int _stepTime;
    int _stepLength;
    
    float _hue;
};

