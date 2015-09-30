#pragma once

#include "LedStrip.h"

class Light {
public:
    Light(LedStrip& ledStrip, int index) : _ledStrip(ledStrip), _singleLedIndex(index), _pIndices(0), _numOfIndices(0) { }
    Light(LedStrip& ledStrip, int* pIndices, int numOfIndices);
    ~Light();

    void setRgb(uint8_t red, uint8_t green, uint8_t blue);
    void setHsi(float hue, float saturation, float intensity);

private:
    void hsi2rgb(float H, float S, float I, uint8_t& outR, uint8_t& outG, uint8_t& outB);

private:
    LedStrip& _ledStrip;
    int _singleLedIndex;
    int* _pIndices;
    int _numOfIndices;
};

