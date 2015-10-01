#include "Light.h"
#include <math.h>

Light::Light(LedStrip& ledStrip, int* pIndices, int numOfIndices) : _ledStrip(ledStrip), _singleLedIndex(-1), _numOfIndices(numOfIndices) {
    _pIndices = new int[_numOfIndices];
    for(int i = 0; i < _numOfIndices; i++) {
        _pIndices[i] = pIndices[i];
    }
}

Light::~Light() {
    if(_pIndices != 0) {
        delete[] _pIndices;
        _pIndices = 0;
    }
}

void Light::setRgb(uint8_t red, uint8_t green, uint8_t blue) {
    int length = getLength();
  
    for(int i = 0; i < length; i++) {
        setRgb(i, red, green, blue);
    }
}

void Light::setHsi(float hue, float saturation, float intensity) {
    uint8_t r, g, b;

    hsi2rgb(hue, saturation, intensity, r, g, b);
    setRgb(r, g, b);
}

void Light::setRgb(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if(_singleLedIndex >= 0) {
        _ledStrip[_singleLedIndex].red = red;
        _ledStrip[_singleLedIndex].green = green;
        _ledStrip[_singleLedIndex].blue = blue;
    } else {
      int ledStripIndex = _pIndices[index];
      _ledStrip[ledStripIndex].red = red;
      _ledStrip[ledStripIndex].green = green;
      _ledStrip[ledStripIndex].blue = blue;
    }
}

void Light::setHsi(int index, float hue, float saturation, float intensity) {
    uint8_t r, g, b;

    hsi2rgb(hue, saturation, intensity, r, g, b);
    setRgb(index, r, g, b);
}

// Based on http://blog.saikoled.com/post/43693602826/why-every-led-light-should-be-using-hsi
void Light::hsi2rgb(float H, float S, float I, uint8_t& outR, uint8_t& outG, uint8_t& outB) {
    int r, g, b;
    H = fmod(H, 1);
    H = 2 * 3.14159 * H; // Convert unit to radians.
    S = S > 0 ? (S < 1 ? S : 1) : 0; // clamp S and I to interval [0,1]
    I = I > 0 ? (I < 1 ? I : 1) : 0;
      
    // Math! Thanks in part to Kyle Miller.
    if(H < 2.09439) {
        r = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
        g = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
        b = 255*I/3*(1-S);
    } else if(H < 4.188787) {
        H = H - 2.09439;
        g = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
        b = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
        r = 255*I/3*(1-S);
    } else {
        H = H - 4.188787;
        b = 255*I/3*(1+S*cos(H)/cos(1.047196667-H));
        r = 255*I/3*(1+S*(1-cos(H)/cos(1.047196667-H)));
        g = 255*I/3*(1-S);
    }
    
    outR = r;
    outG = g;
    outB = b;
}

