#include <FastLED.h>

#include "MadHat.h"

MadHat madHat;

void setup() {
    randomSeed(analogRead(0));
    madHat.init(); 
}

void loop() {
    madHat.update();
}
