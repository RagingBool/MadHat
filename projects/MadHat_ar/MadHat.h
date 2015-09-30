#include "LedStrip.h"

class MadHat {
public:
    MadHat() {}
    
    void init();
    void update();

private:
    LedStrip _ledStrip;
};

