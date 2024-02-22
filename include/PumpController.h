#include "PumpSpeed.h"

#ifndef PumpController_h
#define PumpController_h

class PumpController
{
public:
    PumpController(int transistor1, int transistor2, int transistor3, int transistor4);
    void run(PumpSpeed speed);
    void stop();

private:
    int _transistor1;
    int _transistor2;
    int _transistor3;
    int _transistor4;
    bool _running;
};

#endif