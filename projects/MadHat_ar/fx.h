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

class InterruptingFx : public IFx {
public:
    InterruptingFx(IFx* pMainFx, IFx* pSecondary, int minMainTime, int maxMainTime, int minSecondaryTime, int maxSecondaryTime);

    virtual void reset();
    virtual void poke();
    virtual void update(int dt_millis);
    virtual void render();

private:
    void nextPhase();
    void startMainPhase();
    void startSecondaryPhase();

private:
    IFx* _pMainFx;
    IFx* _pSecondary;
    int _minMainTime;
    int _maxMainTime;
    int _minSecondaryTime;
    int _maxSecondaryTime;

    bool _isMainPhase;
    int _phaseTime;
    int _phaseLength;
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

class ChasingLightsFx : public IFx {
public:
    ChasingLightsFx(Light* pLight, int stepLength, int minLights, int maxLights, float saturation, float intensity);
    virtual ~ChasingLightsFx();

    virtual void reset();
    virtual void poke();
    virtual void update(int dt_millis);
    virtual void render();

private:
    Light* _pLight;

    int _stepLength;
    int _minLights;
    int _maxLights;
    float _saturation;
    float _intensity;

    float* _pHues;
    int _stepTime;
    int _numLights;
    int _phase;
};
