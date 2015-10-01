#include "fx.h"

ColorCycleFx::ColorCycleFx(Light* pLight, int period, float saturation, float intensity) :
    _pLight(pLight),
    _saturation(saturation),
    _intensity(intensity)
{
    _hueLfo.setFrequency(periodToFrequency(period));
    _hueLfo.setLfoFunction(Lfo::SAW_UP);
  
    reset();
}

void ColorCycleFx::reset() {
    _hueLfo.reset();
}

void ColorCycleFx::update(int dt_millis) {
    _hueLfo.update(dt_millis);
    _pLight -> setHsi(_hueLfo.getOutput() / 255.0, _saturation, _intensity);
}

