#include "fx.h"

#include <math.h>
#include <Arduino.h>

InterruptingFx::InterruptingFx(IFx* pMainFx, IFx* pSecondary, int minMainTime, int maxMainTime, int minSecondaryTime, int maxSecondaryTime) :
    _pMainFx(pMainFx),
    _pSecondary(pSecondary),
    _minMainTime(minMainTime),
    _maxMainTime(maxMainTime),
    _minSecondaryTime(minSecondaryTime),
    _maxSecondaryTime(maxSecondaryTime) {

    reset();
}

void InterruptingFx::reset() {
   _pMainFx -> reset();
   _pSecondary -> reset();

   _phaseTime = 0;
   startMainPhase();
}

void InterruptingFx::poke() {
   _pMainFx -> poke();
   _pSecondary -> poke();
}

void InterruptingFx::update(int dt_millis) {
    _phaseTime += dt_millis;

    if(_phaseTime >= _phaseLength) {
        _phaseTime -= _phaseLength;

        nextPhase();
    }
    
    _pMainFx -> update(dt_millis);
    _pSecondary -> update(dt_millis);
}

void InterruptingFx::nextPhase() {
    if(_isMainPhase) {
        startSecondaryPhase();
    } else {
        startMainPhase();
    }
}

void InterruptingFx::startMainPhase() {
    _phaseLength = random(_minMainTime, _maxMainTime);
    _isMainPhase = true;
    _pMainFx -> poke();
}

void InterruptingFx::startSecondaryPhase() {
    _phaseLength = random(_minSecondaryTime, _maxSecondaryTime);
    _isMainPhase = false;
    _pSecondary -> poke();
}

void InterruptingFx::render() {
    if(_isMainPhase) {
        _pMainFx -> render();
    } else {
        _pSecondary -> render();
    }
}

ColorCycleFx::ColorCycleFx(Light* pLight, int period, float saturation, float intensity) :
    _pLight(pLight),
    _saturation(saturation),
    _intensity(intensity) {

    _hueLfo.setFrequency(periodToFrequency(period));
    _hueLfo.setLfoFunction(Lfo::SAW_UP);
  
    reset();
}

void ColorCycleFx::reset() {
    _hueLfo.reset();
}

void ColorCycleFx::update(int dt_millis) {
    _hueLfo.update(dt_millis);
}

void ColorCycleFx::render() {
    _pLight -> setHsi(_hueLfo.getOutput() / 255.0, _saturation, _intensity);
}

FadingEyesFx::FadingEyesFx(Light* pLight, int period, float saturation, float maxIntensity) :
    _pLight(pLight),
    _saturation(saturation),
    _maxIntensity(maxIntensity) {

    _fadeLfo.setFrequency(periodToFrequency(period));
    _fadeLfo.setLfoFunction(Lfo::SAW_DOWN);

    _hue = 0;
  
    reset();
}

void FadingEyesFx::reset() {
    _fadeLfo.reset();
    poke();
}

void FadingEyesFx::poke() {
    _hue = random(1000) / 1000.f;
}

void FadingEyesFx::update(int dt_millis) {
    _fadeLfo.update(dt_millis);
}

void FadingEyesFx::render() {
    float intensity = pow(_fadeLfo.getOutput() / 255.0, 3.f);
    intensity = (intensity > .15f) ? intensity : 0.f;
    
    _pLight -> setHsi(_hue, _saturation, intensity * _maxIntensity);
}

CrazyLightsFx::CrazyLightsFx(Light* pLight, float saturation, float intensity) :
    _pLight(pLight),
    _saturation(saturation),
    _intensity(intensity) {
  
    reset();
}

void CrazyLightsFx::reset() {
    _stepTime = 0;
    nextStep();
}

void CrazyLightsFx::update(int dt_millis) {
    _stepTime += dt_millis;

    if(_stepTime >= _stepLength) {
        _stepTime -= _stepLength;
        nextStep();
    }
}

void CrazyLightsFx::nextStep() {
    _hue = random(1000) / 1000.f;
    _stepLength = random(50, 150);
}

void CrazyLightsFx::render() {
    _pLight -> setHsi(_hue, _saturation, _intensity);
}
