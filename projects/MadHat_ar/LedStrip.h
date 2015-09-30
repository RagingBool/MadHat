#include <FastLED.h>

class LedStrip {
public:
    LedStrip() : _length(0), _data(0) { }
    ~LedStrip();

    void init(int length);

    void sendFrame();

    int getLength() const { return _length; }

    const CRGB& operator[] (int i) const { return _data[i]; }
    CRGB& operator[] (int i) { return _data[i]; }

private:
    int _length;
    CRGB* _data;
};

