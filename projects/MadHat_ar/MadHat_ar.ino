#include <FastLED.h>

#include "MadHat.h"

MadHat madHat(MadHat::MAD_HAT);

void setup() {
    randomSeed(analogRead(0));
    madHat.init(); 
}

void loop() {
    madHat.update();
}
