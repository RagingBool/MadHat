#include "fx.h"

#include <math.h>
#include <Arduino.h>

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

