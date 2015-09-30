#include <FastLED.h>

#include "MadHat.h"

MadHat madHat;

void setup() {
    madHat.init(); 
}

void loop() {
    madHat.update();
}
